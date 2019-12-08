#include <Core/GameObject.h>
#include <memory>
#include <Core/Components/ModelComponent.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Core/Components/LightComponent.h>

#include <Core/Scene.h>
namespace Core
{
	class Scene;
}

std::vector<std::shared_ptr<Core::Components::IComponent>>& Core::GameObject::GetComponents() { return m_components; }

Core::GameObject::GameObject(const GameObject & p_other)
{
	m_components = p_other.m_components;
	m_transform = p_other.m_transform;
}

void Core::GameObject::MoveTo(glm::vec3 & p_vec)
{
	m_transform.SetPos(p_vec);
}

void Core::GameObject::TranslateBy(glm::vec3 & p_vec)
{
	const auto newPos = m_transform.GetPos() + p_vec;
	m_transform.SetPos(newPos);
}

void Core::GameObject::SetTransform(glm::vec3 & p_pos, glm::vec3 & p_rot, glm::vec3 & p_scale)
{
	m_transform.SetTransform(p_pos, p_rot, p_scale);
}

void Core::GameObject::SetTransform(Rendering::Resources::Transform& p_transform)
{
	m_transform = p_transform;
}

void Core::GameObject::AddTexture(const std::string& p_texturePath) const
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	Rendering::Resources::Model& model = *GetComponent<Core::Components::ModelComponent>()->GetModel();
	model.AddTexture(p_texturePath);
}

void Core::GameObject::AddNormalMap(const std::string& p_texturePath) const
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	Rendering::Resources::Model& model = *GetComponent<Core::Components::ModelComponent>()->GetModel();
	model.AddNormalMap(p_texturePath);
}

void Core::GameObject::SetName(const std::string& p_name)
{
	m_name = p_name;
}

std::string Core::GameObject::GetName() const
{
	return m_name;
}

void Core::GameObject::Update(const double p_dt)
{
	m_transform.UpdateModelMatrix();
	UpdateAllComponents(p_dt);
	UpdateShaders();
}

tinyxml2::XMLElement* Core::GameObject::Serialize(tinyxml2::XMLDocument * p_document, tinyxml2::XMLElement * p_gameObjectParentNode)
{
	// Transform
	tinyxml2::XMLElement * transform = p_document->NewElement("Transform");
	tinyxml2::XMLElement * transformPosition = p_document->NewElement("position");
	tinyxml2::XMLElement * transformRotation = p_document->NewElement("rotation");
	tinyxml2::XMLElement * transformScale = p_document->NewElement("scale");

	transformPosition->SetAttribute("x", m_transform.GetPos().x);
	transformPosition->SetAttribute("y", m_transform.GetPos().y);
	transformPosition->SetAttribute("z", m_transform.GetPos().z);

	transformRotation->SetAttribute("x", m_transform.GetRot().x);
	transformRotation->SetAttribute("y", m_transform.GetRot().y);
	transformRotation->SetAttribute("z", m_transform.GetRot().z);

	transformScale->SetAttribute("x", m_transform.GetScale().x);
	transformScale->SetAttribute("y", m_transform.GetScale().y);
	transformScale->SetAttribute("z", m_transform.GetScale().z);

	transform->InsertEndChild(transformPosition);
	transform->InsertEndChild(transformRotation);
	transform->InsertEndChild(transformScale);

	p_gameObjectParentNode->InsertEndChild(transform);

	tinyxml2::XMLElement * gameObjectElement = p_document->NewElement("ListComponent");

	// List of Components of the gameObject
	for (auto & component : m_components)
	{
		tinyxml2::XMLElement * pListElement = p_document->NewElement("Component");
		const std::string componentClassName = typeid(*component).name();
		// beautiful/20: std::string(typeid(component).name()).substr(std::string(typeid(component).name()).find_last_of(':'));
		const size_t index = componentClassName.find_last_of(':');
		const std::string componentName = componentClassName.substr(index + 1);

		pListElement->SetAttribute("name", componentName.c_str());

		tinyxml2::XMLElement * elementReturned = component->Serialize(p_document);
		if (elementReturned)
		{
			pListElement->InsertEndChild(elementReturned);
			gameObjectElement->InsertEndChild(pListElement);
		}
	}
	return gameObjectElement;
}

void Core::GameObject::UpdateAllComponents(const double p_dt)
{
	for (auto& component : m_components)
		component->Update(p_dt);
}

void Core::GameObject::UpdateShaders()
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	const glm::mat4 projection = Rendering::LowRenderer::Camera::GetInstance()->GetProjectionMatrix();
	const glm::mat4 view = Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();

	Rendering::Resources::Model& model = *GetComponent<Core::Components::ModelComponent>()->GetModel();
	Rendering::Resources::Shader& shader = *model.GetShader();

	const glm::mat4 modelMatrix = m_transform.GetModelMatrix();

	const glm::vec3 cameraPos = Rendering::LowRenderer::Camera::GetInstance()->GetPos();

	const auto modelLight = GetComponent<Core::Components::LightComponent>();

	shader.Bind();
	shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
	shader.SetUniformMatrix4fv("u_ProjectionMatrix", projection);
	shader.SetUniformMatrix4fv("u_ViewMatrix", view);
	shader.SetUniform3f("u_ViewPos", cameraPos.x, cameraPos.y, cameraPos.z);

	const auto& lightsInScene = Scene::GetLightsInCurrentScene();
	for (size_t i = 0; i < lightsInScene.size(); ++i)
	{
		const auto& currentLight = lightsInScene[i]->GetLight();
		const auto& uniformName = "u_LightSources[" + std::to_string(i) + "].";
		shader.SetUniform3f(uniformName + "Position", currentLight.Position.x, currentLight.Position.y, currentLight.Position.z);
		shader.SetUniform3f(uniformName + "Color", currentLight.Color.x, currentLight.Color.y, currentLight.Color.z);
		shader.SetUniform3f(uniformName + "Direction", currentLight.Direction.x, currentLight.Direction.y, currentLight.Direction.z);
		shader.SetInt(uniformName + "Type", currentLight.Type);
		shader.SetFloat(uniformName + "Constant", currentLight.Constant);
		shader.SetFloat(uniformName + "Linear", currentLight.Linear);
		shader.SetFloat(uniformName + "Quadratic", currentLight.Quadratic);
		shader.SetFloat(uniformName + "Cutoff", currentLight.Cutoff);
		shader.SetFloat(uniformName + "OuterCutoff", currentLight.OuterCutoff);
		shader.SetFloat(uniformName + "Intensity", currentLight.Intensity);
	}

	if (model.GetTexture()->IsTextureSet())
	{
		shader.SetBool("u_UseTexture", true);
		shader.SetInt("u_DiffuseMap", 0);
	}
	else
	{
		shader.SetBool("u_UseTexture", false);
	}

	if (model.GetNormalMap()->IsTextureSet())
	{
		shader.SetBool("u_EnableNormalMapping", true);
		shader.SetInt("u_NormalMap", 1);
	}
	else
	{
		shader.SetBool("u_EnableNormalMapping", false);
	}
	shader.Unbind();
}

void Core::GameObject::RecompileShaders() const
{
	if (GetComponent<Core::Components::ModelComponent>() == nullptr)
		return;

	Rendering::Resources::Shader& shader = *GetComponent<Core::Components::ModelComponent>()->GetModel()->GetShader();
	shader.RecompileShader();
}
