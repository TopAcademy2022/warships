#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>

#include "notepad-database.h"
#include "game.h"

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::remove("test_save.txt");
        std::remove("empty_test.txt");
        std::remove("corrupt_test.txt");
        std::remove("invalid_coords.txt");
        std::remove("mismatched_type.txt");
    }

    void TearDown() override {
        std::remove("test_save.txt");
        std::remove("empty_test.txt");
        std::remove("corrupt_test.txt");
        std::remove("invalid_coords.txt");
        std::remove("mismatched_type.txt");
    }

    NotepadDatabase database;
};

TEST_F(DatabaseTest, WriteAndReadValidGame) {
    Game originalGame(battlefield::AutomaticMode, battlefield::AutomaticMode);

    bool writeResult = database.WriteDataToFile(originalGame, ".", "test_save", "txt");
    ASSERT_TRUE(writeResult) << "Сохранение игры не удалось";

    Game loadedGame(battlefield::ManualMode, battlefield::ManualMode);
    loadedGame.GetBattlefields().clear();

    bool readResult = database.ReadDataFromFile(loadedGame, ".", "test_save", "txt");
    ASSERT_TRUE(readResult) << "Загрузка игры не удалась";

    const auto& originalBattlefields = originalGame.GetBattlefields();
    const auto& loadedBattlefields = loadedGame.GetBattlefields();

    ASSERT_EQ(originalBattlefields.size(), loadedBattlefields.size())
        << "Количество полей боя не совпадает";

    auto origIt = originalBattlefields.begin();
    auto loadIt = loadedBattlefields.begin();

    for (; origIt != originalBattlefields.end() && loadIt != loadedBattlefields.end();
        ++origIt, ++loadIt) {

        const auto& origShips = origIt->GetShips();
        const auto& loadShips = loadIt->GetShips();

        ASSERT_EQ(origShips.size(), loadShips.size())
            << "Количество кораблей не совпадает";

        auto origShipIt = origShips.begin();
        auto loadShipIt = loadShips.begin();

        for (; origShipIt != origShips.end() && loadShipIt != loadShips.end();
            ++origShipIt, ++loadShipIt) {

            ASSERT_EQ(origShipIt->GetShipType(), loadShipIt->GetShipType())
                << "Тип корабля не совпадает";

            const auto& origDecks = origShipIt->GetDecks();
            const auto& loadDecks = loadShipIt->GetDecks();

            ASSERT_EQ(origDecks.size(), loadDecks.size())
                << "Количество палуб не совпадает";

            auto origDeckIt = origDecks.begin();
            auto loadDeckIt = loadDecks.begin();

            for (; origDeckIt != origDecks.end() && loadDeckIt != loadDecks.end();
                ++origDeckIt, ++loadDeckIt) {
                ASSERT_EQ(origDeckIt->GetPositionX(), loadDeckIt->GetPositionX())
                    << "Координата X не совпадает";
                ASSERT_EQ(origDeckIt->GetPositionY(), loadDeckIt->GetPositionY())
                    << "Координата Y не совпадает";
                ASSERT_EQ(origDeckIt->GetIsHit(), loadDeckIt->GetIsHit())
                    << "Статус попадания не совпадает";
            }
        }
    }
}

TEST_F(DatabaseTest, LoadNonExistentFileReturnsFalse) {
    Game game(battlefield::ManualMode, battlefield::ManualMode);
    game.GetBattlefields().clear();

    
    bool result = database.ReadDataFromFile(game, ".", "nonexistent_file", "txt");
    ASSERT_FALSE(result) << "Загрузка несуществующего файла должна возвращать false";
}

TEST_F(DatabaseTest, LoadEmptyFileReturnsFalse) {
    Game game(battlefield::ManualMode, battlefield::ManualMode);
    game.GetBattlefields().clear();

    std::ofstream emptyFile("empty_test.txt");
    emptyFile.close();

    bool result = database.ReadDataFromFile(game, ".", "empty_test", "txt");
    ASSERT_FALSE(result) << "Загрузка пустого файла должна возвращать false";
}

TEST_F(DatabaseTest, LoadCorruptFileReturnsFalse) {
    Game game(battlefield::ManualMode, battlefield::ManualMode);
    game.GetBattlefields().clear();

    std::ofstream corruptFile("corrupt_test.txt");
    corruptFile << "elapsed-seconds 10\n";
    corruptFile << "battlefield 1\n";
    corruptFile << "ship 3 1,1,0 2,2,0 3,3,0\n";
    corruptFile << "battlefield 2\n";
    corruptFile << "ship 2 1,1,0 2,2,0\n";
    corruptFile << "invalid_line\n"; 
    corruptFile.close();

    bool result = database.ReadDataFromFile(game, ".", "corrupt_test", "txt");
    ASSERT_FALSE(result) << "Загрузка повреждённого файла должна возвращать false";
}

TEST_F(DatabaseTest, InvalidCoordinatesReturnsFalse) {
    Game game(battlefield::ManualMode, battlefield::ManualMode);
    game.GetBattlefields().clear();

    std::ofstream invalidFile("invalid_coords.txt");
    invalidFile << "elapsed-seconds 10\n";
    invalidFile << "battlefield 1\n";
    invalidFile << "ship 3 1,1,0 2,11,0 3,3,0\n"; 
    invalidFile << "battlefield 2\n";
    invalidFile << "ship 2 1,1,0 2,2,0\n";
    invalidFile.close();

    bool result = database.ReadDataFromFile(game, ".", "invalid_coords", "txt");
    ASSERT_FALSE(result) << "Загрузка с неверными координатами должна возвращать false";
}

TEST_F(DatabaseTest, MismatchedShipTypeReturnsFalse) {
    Game game(battlefield::ManualMode, battlefield::ManualMode);
    game.GetBattlefields().clear();

    std::ofstream invalidFile("mismatched_type.txt");
    invalidFile << "elapsed-seconds 10\n";
    invalidFile << "battlefield 1\n";
    invalidFile << "ship 4 1,1,0 2,2,0 3,3,0\n"; 
    invalidFile << "battlefield 2\n";
    invalidFile << "ship 2 1,1,0 2,2,0\n";
    invalidFile.close();

    bool result = database.ReadDataFromFile(game, ".", "mismatched_type", "txt");
    ASSERT_FALSE(result) << "Загрузка с несоответствием типа должна возвращать false";
}