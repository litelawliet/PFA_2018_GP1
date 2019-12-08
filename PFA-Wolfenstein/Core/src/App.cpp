#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Components/PlayerComponent.h>
#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/InputManager.h>
#include <Core/Scene.h>
#include <Core/GameManager.h>
#include <Core/Components/ModelComponent.h>
#include <Core/Components/ColliderComponent.h>
#include <Core/Components/CameraComponent.h>
#include <Core/Tools/FontLoader.h>
#include <Core/Components/WeaponComponent.h>
#include <Core/Components/LightComponent.h>

#include <Audio/AudioClip.h>

int main()
{
	auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>(1024, 768);
	std::unique_ptr<Rendering::Managers::Renderer> renderer = std::make_unique<Rendering::Managers::Renderer>();
	renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();

	Rendering::Managers::InputManager::InitializeFirstInstance(device->GetWindow());

	Core::GameManager gameManager(renderer.get());

	Rendering::LowRenderer::Camera::GetInstance()->SetSensitivitySpeed(20.0f);

	std::shared_ptr<Core::GameObject> car = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> player = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> weaponObject = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> monkey = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> bullet = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> room = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> buildings = std::make_shared<Core::GameObject>();

	std::shared_ptr<Core::GameObject> buildingsLight = std::make_shared<Core::GameObject>();
	Core::Scene scene1{};


	monkey->AddComponent<Core::Components::ModelComponent>("../rsc/models/monkey.fbx");
	weaponObject->AddComponent<Core::Components::ModelComponent>("../rsc/models/Handgun_obj.obj");
	car->AddComponent<Core::Components::ModelComponent>("../rsc/models/standard_car.fbx");
	player->AddComponent<Core::Components::ModelComponent>("../rsc/models/statue.obj");
	bullet->AddComponent<Core::Components::ModelComponent>("../rsc/models/bullet.fbx");
	room->AddComponent<Core::Components::ModelComponent>("../rsc/models/cottage_fbx.fbx");
	buildings->AddComponent<Core::Components::ModelComponent>("../rsc/models/buildings.fbx");

	player->AddComponent<Core::Components::PlayerComponent>();
	player->AddComponent<Core::Components::ColliderComponent>();
	player->AddComponent<Core::Components::WeaponComponent>(weaponObject);
	player->GetComponent<Core::Components::WeaponComponent>()->SetBulletModel(bullet);

	car->AddTexture("../rsc/textures/Tiles_026_basecolor.png");
	car->AddNormalMap("../rsc/textures/Tiles_026_normal.png");
	player->AddTexture("../rsc/textures/Terracota_Tiles_003_basecolor.png");
	player->AddNormalMap("../rsc/textures/Terracota_Tiles_003_normal.png");
	bullet->AddTexture("../rsc/textures/bullet.png");
	bullet->AddNormalMap("../rsc/textures/metal_bullet.png");
	room->AddTexture("../rsc/textures/Terracota_Tiles_003_basecolor.png");
	room->AddNormalMap("../rsc/textures/cottage_normal.png");
	buildings->AddTexture("../rsc/textures/Tiles_026_basecolor.png");
	buildings->AddNormalMap("../rsc/textures/Tiles_026_normal.png");

	scene1.AddGameObject(monkey, "monkey");
	scene1.AddGameObject(car, "car");
	scene1.AddGameObject(player, "player");
	scene1.AddGameObject(weaponObject, "weapon");
	scene1.AddGameObject(room, "room");
	scene1.AddGameObject(buildings, "buildings");
	scene1.AddGameObject(buildingsLight, "buildingsLight");

	gameManager.AddScene(scene1);
	gameManager.SetActiveScene(0);

	glm::vec3 weaponPos = glm::vec3(0.1f, -0.05f, 2.7f);
	glm::vec3 weaponRotation = glm::vec3(0, 90, 0);
	glm::vec3 weaponScale = glm::vec3(0.05f, 0.05f, 0.05f);

	glm::vec3 carPosition = glm::vec3(1.0f, 0, 0);
	glm::vec3 carRotation = glm::vec3(0, 0, 36);
	glm::vec3 carScale = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 playerPos = glm::vec3(0.0f, 0, 3.0f);
	glm::vec3 playerRotation = glm::vec3(0, 0, 0);
	glm::vec3 playerScale = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 monkeyPosition = glm::vec3(2.0f, 1.0f, 0.0f);
	glm::vec3 monkeyRotation = glm::vec3(0, 0, 0);
	glm::vec3 monkeyScale = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 bulletPos = glm::vec3(0.1f, -0.05f, 2.7f);
	glm::vec3 bulletRotation = glm::vec3(0, 0, 0);
	glm::vec3 bulletScale = glm::vec3(0.1f, 0.1f, 0.1f);

	glm::vec3 roomPos = glm::vec3(5.0f, -0.0f, 2.7f);
	glm::vec3 roomRotation = glm::vec3(0, 0, 0);
	glm::vec3 roomScale = glm::vec3(0.001f, 0.001f, 0.001f);

	glm::vec3 buildingsPos = glm::vec3(-5.0f, 0.0f, -2.0f);
	glm::vec3 buildingsRotation = glm::vec3(0, 0, 0);
	glm::vec3 buildingsScale = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 buildingsLightPos = glm::vec3(-5.0f, -0.0f, 0.0f);
	glm::vec3 buildingsLightRotation = glm::vec3(0, 0, 0);
	glm::vec3 buildingsLightScale = glm::vec3(1.0f, 1.0f, 1.0f);

	player->AddComponent<Core::Components::LightComponent>(glm::vec3{ 1.0f, 1.0f, 1.0f });
	monkey->AddComponent<Core::Components::LightComponent>(glm::vec3{ 0.0f, 1.0f, 0.0f });
	buildingsLight->AddComponent<Core::Components::LightComponent>(glm::vec3{ 1.0f, 0.f, 0.0f });

	// Buildings light
	const auto& lightBuilding = buildingsLight->GetComponent<Core::Components::LightComponent>();
	lightBuilding->SetType(Core::Components::LIGHT_TYPE::POINT_LIGHT);
	lightBuilding->SetDirection(glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)));
	lightBuilding->SetConstant(1.0f);
	lightBuilding->SetLinear(0.5f);
	lightBuilding->SetQuadratic(0.2f);
	lightBuilding->SetIntensity(1.0f);

	// Settings the player light
	const auto& light = player->GetComponent<Core::Components::LightComponent>();
	light->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	light->SetDirection(glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)));
	light->SetType(Core::Components::LIGHT_TYPE::DIRECTIONAL_LIGHT);
	light->SetConstant(1.0f);
	light->SetLinear(0.5f);
	light->SetQuadratic(0.2f);
	light->SetCutoff(0.0f);
	light->SetOuterCutoff(1.0f);

	// Settings the monekylight
	const auto& monkeyLight = monkey->GetComponent<Core::Components::LightComponent>();
	monkeyLight->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//light->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	monkeyLight->SetDirection(glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)));
	monkeyLight->SetType(Core::Components::LIGHT_TYPE::POINT_LIGHT);
	monkeyLight->SetConstant(1.0f);
	monkeyLight->SetLinear(0.5f);
	monkeyLight->SetQuadratic(0.2f);
	monkeyLight->SetCutoff(0.0f);
	monkeyLight->SetOuterCutoff(1.0f);
	monkeyLight->SetIntensity(0.1f);

	Core::GameManager::GetActiveScene()->FindGameObject("car")->SetTransform(carPosition, carRotation, carScale);
	Core::GameManager::GetActiveScene()->FindGameObject("player")->SetTransform(playerPos, playerRotation, playerScale);
	Core::GameManager::GetActiveScene()->FindGameObject("weapon")->SetTransform(weaponPos, weaponRotation, weaponScale);
	Core::GameManager::GetActiveScene()->FindGameObject("monkey")->SetTransform(monkeyPosition, monkeyRotation, monkeyScale);
	Core::GameManager::GetActiveScene()->FindGameObject("room")->SetTransform(roomPos, roomRotation, roomScale);
	Core::GameManager::GetActiveScene()->FindGameObject("buildings")->SetTransform(buildingsPos, buildingsRotation, buildingsScale);
	Core::GameManager::GetActiveScene()->FindGameObject("buildingsLight")->SetTransform(buildingsLightPos, buildingsLightRotation, buildingsLightScale);
	bullet->SetTransform(bulletPos, bulletRotation, bulletScale);

	Core::Tools::FontLoader fontLoader{};
	Rendering::Resources::Shader fontShader("../rsc/shaders/fontShader.vert", "../rsc/shaders/fontShader.frag");

	Audio::AudioClip weaponShootClip;
	weaponShootClip.Play2DClip("../rsc/audio/music/track.wav", true, 0.5f);
	scene1.Serialize();

	double currentTime = 0.0;
	double dt = 0.0;
	double lastTime = glfwGetTime();

	while (!device->ShouldClose())
	{
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;
		device->RefreshEvent();
		renderer->Clear();

		// ##### Game logic #####
		gameManager.HandleEvents(dt);

		// ##### Update #####
		gameManager.Update(dt);

		// ##### Drawing #####
		gameManager.DrawActiveScene(*renderer);
		//fontLoader.RenderText(fontShader, "Test Text 1234", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		device->Render();
	}

	return EXIT_SUCCESS;
}
