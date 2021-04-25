#include "controls.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This constructor is used to initialize the components
	// of the controls screen.
	// ------------------------------------------------------------
	Controls::Controls(GameCallback* callback)
	{
		m_GameCallback = callback;

		m_Background = new Image("assets/ui/background.png", 0, 0);
		m_ReturnToMenu = new Image("assets/text/return_to_menu_text.png", 16, 32);
		m_KeyBindings = new Image("assets/text/key_bindings_text.png", 16, 125);
		m_LungeAttackExplanation = new Image("assets/text/lunge_attack_explanation_text.png", 64 * 6, 32);
		m_HealExplanation = new Image("assets/text/heal_explanation_text.png", 64 * 6, 32 + (64 * 5));
	}

	// ------------------------------------------------------------
	// This method is used to update the components of the controls
	// screen.
	// ------------------------------------------------------------
	void Controls::Update(float deltaTime)
	{
		if (InputManager::GetInstance()->KeyPressed(KeyBinding::ESCAPE)) {
			m_GameCallback->SetNextState(new StartMenu(m_GameCallback));
		}
	}

	// ------------------------------------------------------------
	// This method is used to draw the components of the controls
	// screen on to the screen.
	// ------------------------------------------------------------
	void Controls::Render(Tmpl8::Surface* screen)
	{
		m_Background->DrawImage(screen);
		m_ReturnToMenu->DrawImage(screen);
		m_KeyBindings->DrawImage(screen);
		m_LungeAttackExplanation->DrawImage(screen);
		m_HealExplanation->DrawImage(screen);
	}
	
	// ------------------------------------------------------------
	// This destructoru is used to safely free the memory of the
	// components on the controls screen.
	// ------------------------------------------------------------
	Controls::~Controls()
	{
		if (m_Background != nullptr) {
			delete m_Background;
			m_Background = nullptr;
		}

		if (m_ReturnToMenu != nullptr) {
			delete m_ReturnToMenu;
			m_ReturnToMenu = nullptr;
		}

		if (m_KeyBindings != nullptr) {
			delete m_KeyBindings;
			m_KeyBindings = nullptr;
		}

		if (m_LungeAttackExplanation != nullptr) {
			delete m_LungeAttackExplanation;
			m_LungeAttackExplanation = nullptr;
		}

		if (m_HealExplanation != nullptr) {
			delete m_HealExplanation;
			m_HealExplanation = nullptr;
		}

		m_GameCallback = nullptr;
	}
}