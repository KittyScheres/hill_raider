#include "Controls.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This constructor is used to initialize the components
	// of the controls screen.
	// ------------------------------------------------------------
	Controls::Controls(GameCallback* iCallback)
	{
		callback = iCallback;

		background = new Image("assets/ui/background.png", 0, 0);
		returnToMenu = new Image("assets/text/return_to_menu_text.png", 16, 32);
		keyBindings = new Image("assets/text/key_bindings_text.png", 16, 125);
		lungeAttackExplanation = new Image("assets/text/lunge_attack_explanation_text.png", 64 * 6, 32);
		healExplanation = new Image("assets/text/heal_explanation_text.png", 64 * 6, 64 * 5);
	}

	// ------------------------------------------------------------
	// This method is used to update the components of the controls
	// screen.
	// ------------------------------------------------------------
	void Controls::Update(float deltaTime)
	{
		if (InputManager::GetInstance()->KeyPressed(InputManager::Keys::ESCAPE)) {
			callback->SetNextState(new StartMenu(callback));
		}
	}

	// ------------------------------------------------------------
	// This method is used to draw the components of the controls
	// screen on to the screen.
	// ------------------------------------------------------------
	void Controls::Render(Tmpl8::Surface* screen)
	{
		background->DrawImage(screen);
		returnToMenu->DrawImage(screen);
		keyBindings->DrawImage(screen);
		lungeAttackExplanation->DrawImage(screen);
		healExplanation->DrawImage(screen);
	}
	
	// ------------------------------------------------------------
	// This destructoru is used to safely free the memory of the
	// components on the controls screen.
	// ------------------------------------------------------------
	Controls::~Controls()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		if (returnToMenu != nullptr) {
			delete returnToMenu;
			returnToMenu = nullptr;
		}

		if (keyBindings != nullptr) {
			delete keyBindings;
			keyBindings = nullptr;
		}

		if (lungeAttackExplanation != nullptr) {
			delete lungeAttackExplanation;
			lungeAttackExplanation = nullptr;
		}

		if (healExplanation != nullptr) {
			delete healExplanation;
			healExplanation = nullptr;
		}

		callback = nullptr;
	}
}