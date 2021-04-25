#include "player.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for a player entity.
	// --------------------------------------------------
	Player::Player(int x, int y): Entity(x, y, 28, 62)
	{
		m_InputManager = InputManager::GetInstance();
		m_LegsAnimation = new Animation("assets/entities/black_ant_legs.png", 4, 4, c_TimePerframeWalkingAnimation, x, y, true);
		m_BodyAnimation = new Animation("assets/entities/black_ant_body.png", 4, 4, 75.f, x, y, false);
		m_AttackHitbox = new Hitbox(m_X, m_Y + m_AttackHitboxOffset, c_AttackHitboxWidth, c_AttackHitboxHeight);
	}

	// --------------------------------------------------
	// This method is used to update a player entity.
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		if (m_InputManager->KeyPressed(KeyBinding::E)) {
			Heal();
		}

		if (!m_LungeFlag) {
			CheckForMovementKeyPressed();
			CheckForMovementKeyLetGo();
			MovePlayer(deltaTime);
			
			if (!m_LungeCooldownFlag) {
				if (m_InputManager->KeyPressed(KeyBinding::SPACE)) {
					m_LegsAnimation->SetTimePerFrame(c_LungeTimePerFrameWalkingAnimation);
					m_LungeFlag = true;
					m_LungeCooldownFlag = true;
				}
			}
			else {
				//attack cooldown timer
				if (m_LungeCooldownTimer >= c_LungeCooldown) {
					m_LungeCooldownFlag = false;
					m_LungeCooldownTimer = 0.f;
					m_BodyAnimation->SetCurrentXFrame(0);
				}
				else {
					m_LungeCooldownTimer += deltaTime;
					m_BodyAnimation->UpdateAnimation(deltaTime);
				}
			}
		}
		else {
			//is attacking
			m_LegsAnimation->UpdateAnimation(deltaTime);
			Lunge(deltaTime);

			if (m_LungeDurationTimer >= c_LungeDuration) {
				m_LegsAnimation->SetTimePerFrame(c_TimePerframeWalkingAnimation);
				m_LungeFlag = false;
				m_LungeDurationTimer = 0.f;
			}
			else {
				m_LungeDurationTimer += deltaTime;
			}
		}

		SetPosition(m_X, m_Y);
	}
	
	// --------------------------------------------------
	// This method is used to process the collisions between
	// a player entity and other entities.
	// --------------------------------------------------
	void Player::LateUpdate(TileMap* tileMap, std::list<Entity*> entityList)
	{
		ProcessTileMapCollision(tileMap);

		for (Entity* entity : entityList) {
			FoodPointsPickup* foodPointPickup = dynamic_cast<FoodPointsPickup*>(entity);

			//entity on entity collision
			if (foodPointPickup == nullptr) {
				if (TestBoxCollision(m_Hitbox, entity)) {
					ApplyEntityCollision(entity);
					SetPosition(m_X, m_Y);
				}
			}

			//entity on attack hitbox collision
			if (m_LungeFlag && foodPointPickup == nullptr) {
				if (TestBoxCollision(m_AttackHitbox, entity)) {
					EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(entity);
					if (enemyAnt != nullptr) {
						enemyAnt->TakeDamage();
						m_LungeFlag = false;
						m_LungeDurationTimer = 0.f;
					}
				}
			}

			//entity on food points pickup entity collision
			if (foodPointPickup != nullptr) {
				if (TestBoxCollision(m_Hitbox, entity)) {
					GameData* gameDataInstance = GameData::GetInstance();
					gameDataInstance->m_PlayerPoints += foodPointPickup->GetPoints();
					if (gameDataInstance->m_PlayerPoints > gameDataInstance->c_s_MaxPoints) {
						gameDataInstance->m_PlayerPoints -= gameDataInstance->m_PlayerPoints % gameDataInstance->c_s_MaxPoints;
					}
					foodPointPickup->RemoveFoodPointsPickup();
				}
			}
		}
	}

	// --------------------------------------------------
	// This method is used to draw a player entity on
	// to the screen.
	// --------------------------------------------------
	void Player::Render(Tmpl8::Surface* screen)
	{
		m_LegsAnimation->SetPosition(m_X - (m_BodyAnimation->GetWidth() / 2), m_Y - (m_BodyAnimation->GetHeight() / 2));
		m_BodyAnimation->SetPosition(m_X - (m_BodyAnimation->GetWidth() / 2), m_Y - (m_BodyAnimation->GetHeight() / 2));
		
		m_LegsAnimation->DrawAnimation(screen);
		m_BodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	// This method is called to make a player entity take
	// damage.
	// --------------------------------------------------
	void Player::TakeDamage() {
		--GameData::GetInstance()->m_PlayerHealth;
	}

	// --------------------------------------------------
	// This method is used to set the gameplay callback
	// for the player.
	// --------------------------------------------------
	void Player::SetGamePlayCallback(GameplayCallback* callback) {
		m_GameplayCallback = callback;
	}

	// --------------------------------------------------
	// This method is used to set the position of a player
	// entity.
	// --------------------------------------------------
	void Player::SetPosition(int x, int y) {
		m_X = x;
		m_Y = y;
		m_Hitbox->SetPosition(m_X, m_Y);

		switch (m_Direction)
		{
		case Direction::UP :
		case Direction::DOWN :
			m_AttackHitbox->SetPosition(m_X, m_Y + m_AttackHitboxOffset);
			break;

		case Direction::LEFT :
		case Direction::RIGHT :
			m_AttackHitbox->SetPosition(m_X + m_AttackHitboxOffset, m_Y);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to set the direction a player
	// entity is facing.
	// --------------------------------------------------
	void Player::SetDirection(Direction direction) {
		m_Direction = direction;

		m_LegsAnimation->SetCurrentYFrame((int)m_Direction);
		m_BodyAnimation->SetCurrentYFrame((int)m_Direction);

		switch (m_Direction)
		{
		case Direction::UP:
			m_AttackHitboxOffset = -std::abs(m_AttackHitboxOffset);
			m_Hitbox->SetWidth(m_Width);
			m_Hitbox->SetHeight(m_Height);
			m_AttackHitbox->SetWidth(c_AttackHitboxWidth);
			m_AttackHitbox->SetHeight(c_AttackHitboxHeight);
			break;
		
		case Direction::RIGHT:
			m_AttackHitboxOffset = std::abs(m_AttackHitboxOffset);
			m_Hitbox->SetWidth(m_Height);
			m_Hitbox->SetHeight(m_Width);
			m_AttackHitbox->SetWidth(c_AttackHitboxHeight);
			m_AttackHitbox->SetHeight(c_AttackHitboxWidth);
			break;

		case Direction::DOWN:
			m_AttackHitboxOffset = std::abs(m_AttackHitboxOffset);
			m_Hitbox->SetWidth(m_Width);
			m_Hitbox->SetHeight(m_Height);
			m_AttackHitbox->SetWidth(c_AttackHitboxWidth);
			m_AttackHitbox->SetHeight(c_AttackHitboxHeight);
			break;

		case Direction::LEFT:
			m_AttackHitboxOffset = -std::abs(m_AttackHitboxOffset);
			m_Hitbox->SetWidth(m_Height);
			m_Hitbox->SetHeight(m_Width);
			m_AttackHitbox->SetWidth(c_AttackHitboxHeight);
			m_AttackHitbox->SetHeight(c_AttackHitboxWidth);
			break;
		}
	}

	// --------------------------------------------------
	// This methos is used to get the direction a player
	// entity.
	// --------------------------------------------------
	Direction Player::GetDirection() {
		return m_Direction;
	}

	// --------------------------------------------------
	// This method is used to get the sprite of a player
	// entity.
	// --------------------------------------------------
	Animation* Player::GetSprite()
	{
		return m_BodyAnimation;
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the propeties of a player entity.
	// --------------------------------------------------
	Player::~Player()
	{
		if (m_LegsAnimation != nullptr) {
			delete m_LegsAnimation;
			m_LegsAnimation = nullptr;
		}

		if (m_BodyAnimation != nullptr) {
			delete m_BodyAnimation;
			m_BodyAnimation = nullptr;
		}

		if (m_AttackHitbox != nullptr) {
			delete m_AttackHitbox;
			m_AttackHitbox = nullptr;
		}

		m_GameplayCallback = nullptr;
		m_InputManager = nullptr;
	}

	// --------------------------------------------------
	// This method is used to check if a new direction key
	// has been pressed.
	// --------------------------------------------------
	void Player::CheckForMovementKeyPressed()
	{
		if (m_InputManager->KeyPressed(KeyBinding::UP)) {
			SetDirection(Direction::UP);
		}

		if (m_InputManager->KeyPressed(KeyBinding::RIGHT)) {
			SetDirection(Direction::RIGHT);
		}

		if (m_InputManager->KeyPressed(KeyBinding::DOWN)) {
			SetDirection(Direction::DOWN);
		}

		if (m_InputManager->KeyPressed(KeyBinding::LEFT)) {
			SetDirection(Direction::LEFT);
		}
	}

	// --------------------------------------------------
	// This method is used to check if the direction key 
	// of the current direction has been let go of.
	// --------------------------------------------------
	void Player::CheckForMovementKeyLetGo()
	{
		switch (m_Direction)
		{
		case Direction::UP:
			if (m_InputManager->KeyLetGo(KeyBinding::UP)) {
				if (m_InputManager->KeyDown(KeyBinding::RIGHT)) {
					SetDirection(Direction::RIGHT);
				}
				else if (m_InputManager->KeyDown(KeyBinding::DOWN)) {
					SetDirection(Direction::DOWN);
				}
				else if (m_InputManager->KeyDown(KeyBinding::LEFT)) {
					SetDirection(Direction::LEFT);
				}
			}
			break;

		case Direction::RIGHT:
			if (m_InputManager->KeyLetGo(KeyBinding::RIGHT)) {
				if (m_InputManager->KeyDown(KeyBinding::DOWN)) {
					SetDirection(Direction::DOWN);
				}
				else if (m_InputManager->KeyDown(KeyBinding::LEFT)) {
					SetDirection(Direction::LEFT);
				}
				else if (m_InputManager->KeyDown(KeyBinding::UP)) {
					SetDirection(Direction::UP);
				}
			}
			break;

		case Direction::DOWN:
			if (m_InputManager->KeyLetGo(KeyBinding::DOWN)) {
				if (m_InputManager->KeyDown(KeyBinding::LEFT)) {
					SetDirection(Direction::LEFT);
				}
				else if (m_InputManager->KeyDown(KeyBinding::UP)) {
					SetDirection(Direction::UP);
				}
				else if (m_InputManager->KeyDown(KeyBinding::RIGHT)) {
					SetDirection(Direction::RIGHT);
				}
			}
			break;

		case Direction::LEFT:
			if (m_InputManager->KeyLetGo(KeyBinding::LEFT)) {
				if (m_InputManager->KeyDown(KeyBinding::UP)) {
					SetDirection(m_Direction = Direction::UP);
				}
				else if (m_InputManager->KeyDown(KeyBinding::RIGHT)) {
					SetDirection(m_Direction = Direction::RIGHT);
				}
				else if (m_InputManager->KeyDown(KeyBinding::DOWN)) {
					SetDirection(m_Direction = Direction::DOWN);
				}
			}
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to move a player entity in the
	// current direction.
	// --------------------------------------------------
	void Player::MovePlayer(float deltaTime)
	{
		m_DistanceMoved = 0;

		switch (m_Direction)
		{
		case Direction::UP:
			if (m_InputManager->KeyDown(KeyBinding::UP)) {
				m_LegsAnimation->UpdateAnimation(deltaTime);
				m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
				m_Y -= m_DistanceMoved;
			}
			break;

		case Direction::RIGHT:
			if (m_InputManager->KeyDown(KeyBinding::RIGHT)) {
				m_LegsAnimation->UpdateAnimation(deltaTime);
				m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
				m_X += m_DistanceMoved;
			}
			break;

		case Direction::DOWN:
			if (m_InputManager->KeyDown(KeyBinding::DOWN)) {
				m_LegsAnimation->UpdateAnimation(deltaTime);
				m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
				m_Y += m_DistanceMoved;
			}
			break;

		case Direction::LEFT:
			if (m_InputManager->KeyDown(KeyBinding::LEFT)) {
				m_LegsAnimation->UpdateAnimation(deltaTime);
				m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
				m_X -= m_DistanceMoved;
			}
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to move a player entity in 
	// the current direction with an increade movement
	// speed.
	// --------------------------------------------------
	void Player::Lunge(float deltaTime)
	{
		m_DistanceMoved = 0;

		switch (m_Direction)
		{
		case Direction::UP:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_Y -= m_DistanceMoved;
			break;

		case Direction::RIGHT:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_X += m_DistanceMoved;
			break;

		case Direction::DOWN:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_Y += m_DistanceMoved;
			break;

		case Direction::LEFT:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_X -= m_DistanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used heal the player when the 
	// conditions have been met.
	// --------------------------------------------------
	void Player::Heal()
	{
		GameData* gameDataInstance = GameData::GetInstance();
		if (gameDataInstance->m_PlayerHealth < gameDataInstance->c_s_MaxHealth && gameDataInstance->m_PlayerPoints >= gameDataInstance->c_s_PointsForHealth) {
			++gameDataInstance->m_PlayerHealth;
			gameDataInstance->m_PlayerPoints -= gameDataInstance->c_s_PointsForHealth;
		}
	}

	// --------------------------------------------------
	// This method is used to process tile map collision
	// for the player.
	// --------------------------------------------------
	void Player::ProcessTileMapCollision(TileMap* tileMap) {
		char tileMapCollisionChar = ' ';
		short hitboxPointIndex = -1;
		CheckTileMapCollision(hitboxPointIndex, tileMapCollisionChar, tileMap);
		
		switch (tileMapCollisionChar)
		{
		case 'w':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->MovePlayerToNextRoom(Direction::UP);
				SetPosition((7 * 64) + (GetSprite()->GetWidth() / 2), (7 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'd':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->MovePlayerToNextRoom(Direction::RIGHT);
				SetPosition(64 + (GetSprite()->GetWidth() / 2), (4 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 's':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->MovePlayerToNextRoom(Direction::DOWN);
				SetPosition((7 * 64) + (GetSprite()->GetWidth() / 2), 64 + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'a':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->MovePlayerToNextRoom(Direction::LEFT);
				SetPosition((13 * 64) + (GetSprite()->GetWidth() / 2), (4 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 't':
		case 'g':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->PlayerHasWonTheGame();
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'h':
		case 'f':
			if (m_GameplayCallback->HasRoomBeenCleared()) {
				m_GameplayCallback->PlayerHasWonTheGame();
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 'x':
			switch (m_Direction)
			{
			case Direction::UP:
			case Direction::DOWN:
				ApplyVerticalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][1]);
				break;

			case Direction::LEFT:
			case Direction::RIGHT:
				ApplyHorizontalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][0]);
				break;
			}
			break;
		}
	}
}