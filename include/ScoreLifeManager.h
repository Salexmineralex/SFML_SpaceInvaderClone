#pragma once
#include "ProgressBar.h"
#include "MyText.h"


class ScoreLifeManager{
public:

    //Constructors

    ScoreLifeManager();
    ScoreLifeManager(int score,int life);
    ~ScoreLifeManager();


    void addLife(int heal);
    void substractLife(int damage);

    void addScore(int addScore);
    void substractScore(int subsScore);

    int getLife();
    int getScore();

private:

    // Atributos
    ProgressBar* m_life_progress_bar = nullptr;
    MyText* m_score_text = nullptr;
    int m_score;
    int m_life;

    //CONST VARIABLES

    const int m_maxLife;

    //Methods
    void createScoreText();
    

};