#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SinkTheFleet/src/safeio.cpp"
#include "../../SinkTheFleet/src/textGraphics.cpp"
#include "../../SinkTheFleet/src/fleet.h"
#include "../../SinkTheFleet/src/fleet.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SinkTheFleetTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(IsValidLocationTest)
		{
			const char smallGrid = 'S';
			const char largeGrid = 'L';
			Player players[NUMPLAYERS];

			// Initialize Game
			initializePlayer(players);
			initializePlayer(players + 1);
			allocMem(players, largeGrid);

			// Test Valid Locations
			CheckValidLocation(players[0], largeGrid);
			
			// Cleanup
			deleteMem(players, largeGrid);


		}
		bool CheckValidLocation(Player p, char gridSize) {
			bool result;
			
			p.m_ships[Ship::CARRIER].m_bowLocation = { 0, 12 };
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsTrue(result);

			p.m_ships[Ship::CARRIER].m_bowLocation = { 12, 0 };
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsTrue(result);

			p.m_ships[Ship::CARRIER].m_bowLocation = { 12, 12 };
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsFalse(result);

			p.m_ships[Ship::CARRIER].m_bowLocation = { 12, 12 };
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsFalse(result);

			return true;
			/*result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsFalse(result);
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsFalse(result);
			result = isValidLocation(p, Ship::CARRIER, gridSize);
			Assert::IsFalse(result);*/
		}

	};
}