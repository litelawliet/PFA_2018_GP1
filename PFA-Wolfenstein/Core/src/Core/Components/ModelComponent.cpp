#include <stdafx.h>
#include <Core/Components/ModelComponent.h>
#include <Rendering/LowRenderer/Camera.h>

using namespace Core::Components;

ModelComponent::ModelComponent(Core::GameObject& p_gameObject) : m_gameObject{ p_gameObject }
{
	m_model = nullptr;
	m_type = "Model";
}

ModelComponent::ModelComponent(Core::GameObject& p_gameObject, const std::string& p_path) : m_gameObject{ p_gameObject }
{
	m_model = std::make_unique<Rendering::Resources::Model>(Rendering::Resources::Model(p_path));
}

ModelComponent::~ModelComponent()
{
}

ModelComponent::ModelComponent(const ModelComponent & p_other) : m_gameObject{ p_other.m_gameObject }
{
	m_type = p_other.m_type;
	m_model = p_other.m_model;
}

void Core::Components::ModelComponent::Update(const double p_dt)
{
	const glm::mat4 projection = Rendering::LowRenderer::Camera::GetInstance()->GetProjectionMatrix();
	const glm::mat4 view = Rendering::LowRenderer::Camera::GetInstance()->GetViewMatrix();

	const glm::mat4 modelMatrix = m_gameObject.GetTransform().GetModelMatrix();

	m_model->GetShader()->Bind();
	m_model->GetShader()->SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
	m_model->GetShader()->SetUniformMatrix4fv("u_ProjectionMatrix", projection);
	m_model->GetShader()->SetUniformMatrix4fv("u_ViewMatrix", view);
	m_model->GetShader()->Unbind();
}

tinyxml2::XMLElement* ModelComponent::Serialize(tinyxml2::XMLDocument* p_document)
{
	tinyxml2::XMLElement * model = p_document->NewElement("Model");

	const auto& modelShader = m_model->GetShader();

	model->SetAttribute("modelPath", m_model->GetModelPath().c_str());
	model->SetAttribute("vertexPath", modelShader->GetVertexShaderPath().c_str());
	model->SetAttribute("fragmentPath", modelShader->GetFragmentShaderPath().c_str());
	model->SetAttribute("texturePath", m_model->GetTexture()->GetTexturePath().c_str());
	model->SetAttribute("normalMapPath", m_model->GetNormalMap()->GetTexturePath().c_str());

	return model;
}

const std::shared_ptr<Rendering::Resources::Mesh>& ModelComponent::GetMesh() const
{
	return m_model->GetMesh();
}

const std::shared_ptr<Rendering::Resources::Model>& ModelComponent::GetModel() const
{
	return m_model;
}
