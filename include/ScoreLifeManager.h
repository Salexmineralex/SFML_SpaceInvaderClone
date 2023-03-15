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
 
    int m_score;
    int m_life;
    int m_maxLife = 100;
    ProgressBar* m_life_progress_bar = nullptr;
    MyText* m_score_text = nullptr;

    //Methods
    void createScoreText();
    

};