#include <Core/Components/LightComponent.h>

Core::Components::LightComponent::LightComponent(GameObject& p_gameObject, const glm::vec3 & p_color)
	: m_gameObject{ p_gameObject }, m_light{}
{
	m_light.Color = p_color;
	m_light.Type = static_cast<int>(LIGHT_TYPE::DIRECTIONAL_LIGHT);
	m_light.Intensity = 1.0f;
}

Core::Components::LightComponent::LightComponent(const LightComponent& p_other)
	: m_gameObject{ p_other.m_gameObject }, m_light{ p_other.m_light }
{
}

void Core::Components::LightComponent::Update(const double p_dt)
{
}

tinyxml2::XMLElement* Core::Components::LightComponent::Serialize(tinyxml2::XMLDocument* p_document)
{
	tinyxml2::XMLElement * light = p_document->NewElement("Light");
	tinyxml2::XMLElement * lightPosition = p_document->NewElement("position");
	tinyxml2::XMLElement * lightColor = p_document->NewElement("color");
	tinyxml2::XMLElement * lightDirection = p_document->NewElement("direction");
	tinyxml2::XMLElement * lightType = p_document->NewElement("type");
	tinyxml2::XMLElement * lightConstant = p_document->NewElement("constant");
	tinyxml2::XMLElement * lightLinear = p_document->NewElement("linear");
	tinyxml2::XMLElement * lightQuadratic = p_document->NewElement("quadratic");
	tinyxml2::XMLElement * lightCutoff = p_document->NewElement("cutoff");
	tinyxml2::XMLElement * lightOuterCutoff = p_document->NewElement("outerCutoff");
	tinyxml2::XMLElement * lightIntensity = p_document->NewElement("intensity");

	lightPosition->SetAttribute("x", m_light.Position.x);
	lightPosition->SetAttribute("y", m_light.Position.y);
	lightPosition->SetAttribute("z", m_light.Position.z);

	lightColor->SetAttribute("x", m_light.Color.x);
	lightColor->SetAttribute("y", m_light.Color.y);
	lightColor->SetAttribute("z", m_light.Color.z);

	lightDirection->SetAttribute("x", m_light.Direction.x);
	lightDirection->SetAttribute("y", m_light.Direction.y);
	lightDirection->SetAttribute("z", m_light.Direction.z);
	
	lightType->SetAttribute("type", m_light.Type);
	lightConstant->SetAttribute("constant", m_light.Constant);
	lightLinear->SetAttribute("linear", m_light.Linear);
	lightQuadratic->SetAttribute("quadratic", m_light.Quadratic);
	lightCutoff->SetAttribute("cutoff", m_light.Cutoff);
	lightOuterCutoff->SetAttribute("outerCutoff", m_light.OuterCutoff);
	lightIntensity->SetAttribute("intensity", m_light.Intensity);

	light->InsertEndChild(lightPosition);
	light->InsertEndChild(lightColor);
	light->InsertEndChild(lightDirection);
	light->InsertEndChild(lightType);
	light->InsertEndChild(lightConstant);
	light->InsertEndChild(lightLinear);
	light->InsertEndChild(lightQuadratic);
	light->InsertEndChild(lightCutoff);
	light->InsertEndChild(lightIntensity);

	return light;
}

void Core::Components::LightComponent::AddLight(const LIGHT_TYPE & p_type, const glm::vec3& p_color, const glm::vec3& p_position, const float p_intensity)
{
	m_light.Type = static_cast<int>(p_type);
	m_light.Color = p_color;
	m_light.Position = p_position;
	m_light.Intensity = p_intensity;
}

void Core::Components::LightComponent::PresetDirectionalLight(const glm::vec3& p_color, const glm::vec3& p_position,
	const glm::vec3& p_direction, const float p_intensity)
{
	m_light.Type = static_cast<int>(LIGHT_TYPE::DIRECTIONAL_LIGHT);
	m_light.Color = p_color;
	m_light.Position = p_position;
	m_light.Direction = p_direction;
	m_light.Intensity = p_intensity;
}

void Core::Components::LightComponent::PresetPointLight(const float p_constant, const float p_linear,
	const float p_quadratic, const float p_intensity, const glm::vec3& p_color, const glm::vec3& p_position, const glm::vec3& p_direction)
{
	m_light.Type = static_cast<int>(LIGHT_TYPE::POINT_LIGHT);
	m_light.Constant = p_constant;
	m_light.Linear = p_linear;
	m_light.Quadratic = p_quadratic;
	m_light.Color = p_color;
	m_light.Position = p_position;
	m_light.Direction = p_direction;
	m_light.Intensity = p_intensity;
}

void Core::Components::LightComponent::PresetSpotLight()
{
	m_light.Type = static_cast<int>(LIGHT_TYPE::SPOT_LIGHT);
}

void Core::Components::LightComponent::SetConstant(const float p_constant)
{
	m_light.Constant = p_constant;
}

void Core::Components::LightComponent::SetLinear(const float p_linear)
{
	m_light.Linear = p_linear;
}

void Core::Components::LightComponent::SetQuadratic(const float p_quadratic)
{
	m_light.Quadratic = p_quadratic;
}

void Core::Components::LightComponent::SetCutoff(const float p_cutoff)
{
	m_light.Cutoff = p_cutoff;
}

void Core::Components::LightComponent::SetOuterCutoff(const float p_outerCutoff)
{
	m_light.OuterCutoff = p_outerCutoff;
}

void Core::Components::LightComponent::SetPosition(const glm::vec3& p_position)
{
	m_light.Position = p_position;
}

void Core::Components::LightComponent::SetColor(const glm::vec3& p_color)
{
	m_light.Color = p_color;
}

void Core::Components::LightComponent::SetDirection(const glm::vec3& p_direction)
{
	m_light.Direction = p_direction;
}

void Core::Components::LightComponent::SetType(const LIGHT_TYPE & p_type)
{
	m_light.Type = static_cast<int>(p_type);
}

void Core::Components::LightComponent::SetIntensity(const float p_intensity)
{
	m_light.Intensity = p_intensity;
}

const Rendering::LowRenderer::LightSource& Core::Components::LightComponent::GetLight() const
{
	return m_light;
}
