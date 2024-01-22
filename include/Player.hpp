#pragma once

#include <iostream>

class Player
{
    private:
        int m_id;
        static int m_idCounter;
        int m_score;
    public:
        explicit Player();
        ~Player();

        void AddScore(int score);

        std::string ToString() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

        int GetId() const;
        int GetScore() const;
};