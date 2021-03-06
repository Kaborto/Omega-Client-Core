#include "bddInternalHandler.hpp"
#include "GestionnaireDB.h"

#include <iostream>
#include <sstream>
#include <map>

using namespace std;

bddInternalHandler *bddInternalHandler::singleton = NULL;

bddInternalHandler::bddInternalHandler()
{
    db = new GestionnaireDB("internal.db");

    /*

        A surtout ne pas oter les parenthese sans changer le nom de la db plz
        db->query("CREATE TABLE Sounds (idSound char(50), PRIMARY KEY(idSound));");
        db->query("INSERT INTO Sounds VALUES('activated');");
        db->query("CREATE TABLE Musics (idMusic char(50), PRIMARY KEY(idMusic));");
        db->query("INSERT INTO Musics VALUES('OverMore');");
    */

        //---------------------------------------------------------------------------------------

    /*db->query("CREATE TABLE Sounds (idSound INTEGER, nameSound char(50), PRIMARY KEY(idSound));");

        db->query("INSERT INTO Sounds VALUES(0,'activated');");

        //---------------------------------------------------------------------------------------

        db->query("CREATE TABLE Musics (idMusic INTEGER, nameMusic char(50), PRIMARY KEY(idMusic));");

        db->query("INSERT INTO Musics VALUES(0,'OverMore');");

        //---------------------------------------------------------------------------------------

        db->query("CREATE TABLE Sprites (idSprite INTEGER, nomSprite CHAR(50), tailleX INTEGER, tailleY INTEGER, coordX INTEGER, coordY INTEGER, PRIMARY KEY(idSprite));");

        db->query("INSERT INTO Sprites VALUES(0,'herbe1',16,16,0,0);");

        db->query("INSERT INTO Sprites VALUES(1,'chemin1',16,16,0,0);");

        db->query("INSERT INTO Sprites VALUES(2,'chemin2',16,16,0,0);");

        db->query("INSERT INTO Sprites VALUES(100,'scientifiqueFront',18,24,0,0);");

        db->query("INSERT INTO Sprites VALUES(101,'scientifiqueBack',18,24,0,0);");

        db->query("INSERT INTO Sprites VALUES(102,'scientifiqueRight',18,24,0,0);");

        db->query("INSERT INTO Sprites VALUES(103,'scientifiqueLeft',18,24,0,0);");

        //---------------------------------------------------------------------------------------

        db->query("CREATE TABLE Map (idMap INTEGER, largeur INTEGER, longueur INTEGER, couchePrimaire CHAR, coucheStatique CHAR, PRIMARY KEY(idMap));");

        db->query("INSERT INTO Map VALUES(5000000,30,30,16,'12,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,28,0,1,1,1,2,16,0','0');");

    */


    //db->query("CREATE TABLE ElementsPrim (idElemPrim INTEGER, codePassage INTEGER, PRIMARY KEY(idElemPrim));");
    //db->query("CREATE TABLE LinkSprite (idElemPrim INTEGER,idSprite INTEGER, PRIMARY KEY(idElemPrim,idSprite));");


    //db->query("CREATE TABLE Animations (idAnim INTEGER, speed INTEGER, PRIMARY KEY(idAnim));");
    //db->query("CREATE TABLE LinkAnimSprite (idAnim INTEGER,idSprite INTEGER,ordre INTEGER, PRIMARY KEY(idAnim,idSprite));");


}

bddInternalHandler::~bddInternalHandler()
{
    db->close();
}



//----------------------------------SOUNDS-----------------------------------------

vector<string> bddInternalHandler::getListeSounds()
{
    vector<string> resultEnd;
    vector<vector<string> > result = db->query("SELECT nameSound FROM Sounds;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd.push_back(row.back());
    }
    return resultEnd;

}



//-----------------------------------MUSICS------------------------------------------

vector<string> bddInternalHandler::getListeMusics()
{
    vector<string> resultEnd;

    vector<vector<string> > result = db->query("SELECT nameMusic FROM Musics;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd.push_back(row.back());
    }
    return resultEnd;

}



//---------------------------------SPRITES-------------------------------------------

/*
    Pour r�cuper tout les sprites possible de l'�l�ment herbe (idelem = 1)
    vector<string> resultEnd;
    resultEnd=instBddInternalHandler->getListeSpritesElem("1");
    for(vector<string>::iterator i = resultEnd.begin(); i != resultEnd.end();++i)
    {
        cout<<*i<<endl;
    }
*/


string bddInternalHandler::getSpriteName(string idSpriteIn)
{
    string resultEnd;
    vector<vector<string> > result = db->query("SELECT nomSprite FROM Sprites WHERE idSprite ="+idSpriteIn+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    return resultEnd;
}

string bddInternalHandler::getSpriteName(int idSpriteIn)
{
    ostringstream oss;
    oss<<idSpriteIn;
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT nomSprite FROM Sprites WHERE idSprite ="+oss.str()+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    return resultEnd;
}

vector<int> bddInternalHandler::getListeSprites()
{
    vector<int> resultEnd;

    vector<vector<string> > result = db->query("SELECT idSprite FROM Sprites;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        istringstream iss( row.at(0));
        int idSprite;
        iss >> idSprite;
        cout<<idSprite<<endl;
        resultEnd.push_back(idSprite);
    }
    return resultEnd;
}

vector<string> bddInternalHandler::getListeSpritesName()
{
    vector<string> resultEnd;

    vector<vector<string> > result = db->query("SELECT nomSprite FROM Sprites;");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd.push_back(row.back());
    }

    return resultEnd;
}

vector<int> bddInternalHandler::getListeSpritesElem(int idElement)
{
    ostringstream oss;
    oss<<idElement;
    vector<int> resultEnd;

    vector<vector<string> > result = db->query("SELECT idSprite FROM LinkSprite WHERE idElemPrim="+oss.str()+";");

    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        istringstream iss( row.at(0));
        int idSprite;
        iss >> idSprite;
        resultEnd.push_back(idSprite);
    }

    return resultEnd;
}

vector<int> bddInternalHandler::getListeSpritesElem(string idElement)
{
    vector<int> resultEnd;

    vector<vector<string> > result = db->query("SELECT idSprite FROM LinkSprite WHERE idElemPrim="+idElement+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        istringstream iss( row.at(0));
        int idSprite;
        iss >> idSprite;
        resultEnd.push_back(idSprite);
    }

    return resultEnd;
}

vector<string> bddInternalHandler::getListeSpritesNameElem(string idElement)
{
    vector<int> resultInt;
    vector<string> resultEnd;

    ostringstream oss;

    resultInt=this->getListeSpritesElem(idElement);

    for(vector<int>::iterator it=resultInt.begin();it<resultInt.end();++it)
    {
        oss.str("");
        oss<<*it;
        resultEnd.push_back(this->getSpriteName(oss.str()));
    }

    /*
    vector<vector<string> > result = db->query("SELECT Sprites.nomSprite FROM Sprites, LinkSprite WHERE Sprites.idSprite=LinkSprite.idSprite AND LinkSprite.idElemPrim="+idElement+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd.push_back(row.back());
    }
    */

    return resultEnd;
}

//----------------------------------MAPPING-------------------------------------------

vector<string> bddInternalHandler::getMapPrimaire(string idMap)
{
    string resultTemp;

    vector<vector<string> > result = db->query("SELECT couchePrimaire FROM Map WHERE map.idMap="+idMap+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultTemp=row.back();
    }

    string temp="";
    vector<string> resultEnd;

    for(int i=0;i<resultTemp.size();i++)
    {
        if(resultTemp.at(i)==',')
        {
            resultEnd.push_back(temp);
            temp="";
        }
        else
            temp+=resultTemp.at(i);
    }
    resultEnd.push_back(temp);

    return resultEnd;
}

int bddInternalHandler::getMapLargeur(string idMap)
{
    //request pour acqu�rir la tite largeur de notre map
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT largeur FROM Map WHERE map.idMap="+idMap+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convertion du resultat en int
    istringstream iss( resultEnd );
    int largeurMap;
    iss >> largeurMap;

    return largeurMap;
}

int bddInternalHandler::getMapLongueur(string idMap)
{
    //request pour acqu�rir la tite longueur de notre map
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT longueur FROM Map WHERE map.idMap="+idMap+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convertion du resultat en int
    istringstream iss( resultEnd );
    int longueurMap;
    iss >> longueurMap;

    return longueurMap;
}

vector<string> bddInternalHandler::getMapPrimaire(int idMap)
{
    ostringstream oss;
    oss<<idMap;
    string resultTemp;

    vector<vector<string> > result = db->query("SELECT couchePrimaire FROM Map WHERE map.idMap="+oss.str()+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultTemp=row.back();
    }

    string temp="";
    vector<string> resultEnd;

    for(int i=0;i<resultTemp.size();i++)
    {
        if(resultTemp.at(i)==',')
        {
            resultEnd.push_back(temp);
            temp="";
        }
        else
            temp+=resultTemp.at(i);
    }
    resultEnd.push_back(temp);

    return resultEnd;
}

int bddInternalHandler::getMapLargeur(int idMap)
{
    ostringstream oss;
    oss<<idMap;
    //request pour acqu�rir la tite largeur de notre map
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT largeur FROM Map WHERE map.idMap="+oss.str()+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convertion du resultat en int
    istringstream iss( resultEnd );
    int largeurMap;
    iss >> largeurMap;

    return largeurMap;
}

int bddInternalHandler::getMapLongueur(int idMap)
{
    ostringstream oss;
    oss<<idMap;
    //request pour acqu�rir la tite longueur de notre map
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT longueur FROM Map WHERE map.idMap="+oss.str()+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convertion du resultat en int
    istringstream iss( resultEnd );
    int longueurMap;
    iss >> longueurMap;

    return longueurMap;
}

//----------------------------------ANIMATION--------------------------------------

float bddInternalHandler::getVitesseAnimation(string idAnim)
{
    //request for get the speed of the animation
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT speed FROM Animations WHERE Animations.idAnim="+idAnim+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convert the result in float
    istringstream iss( resultEnd );
    float speedAnim;
    iss >> speedAnim;

    return speedAnim;
}

map<int, string> bddInternalHandler::getAnimation(string idAnim)
{
    map<int, string> listeAnim;

    vector<vector<string> > result = db->query("SELECT idSprite, ordre FROM LinkAnimSprite WHERE LinkAnimSprite.idAnim="+idAnim+";");


    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        //get the order of the srite in the animation and convert him in integer
        istringstream iss( row.at(1));
        int ordre;
        iss >> ordre;
        //get the name of the sprite with his id
        string sprite=getSpriteName(row.at(0));
        //filled the map listeAnim with the order of the sprite in the animation and the name of the sprite
        listeAnim[ordre]=sprite;
    }

    return listeAnim;
}

float bddInternalHandler::getVitesseAnimation(int idAnim)
{
    ostringstream oss;
    oss<<idAnim;
    //request for get the speed of the animation
    string resultEnd;

    vector<vector<string> > result = db->query("SELECT speed FROM Animations WHERE Animations.idAnim="+oss.str()+";");
    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        resultEnd=row.back();
    }
    //convert the result in integer
    istringstream iss( resultEnd );
    float speedAnim;
    iss >> speedAnim;

    return speedAnim;
}

map<int, string> bddInternalHandler::getAnimation(int idAnim)
{
    ostringstream oss;
    oss<<idAnim;
    map<int, string> listeAnim;

    vector<vector<string> > result = db->query("SELECT idSprite, ordre FROM LinkAnimSprite WHERE LinkAnimSprite.idAnim="+oss.str()+";");


    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        //get the order of the srite in the animation and convert him in integer
        istringstream iss( row.at(1));
        int ordre;
        iss >> ordre;
        //get the name of the sprite with his id
        string sprite=getSpriteName(row.at(0));
        //filled the map listeAnim with the order of the sprite in the animation and the name of the sprite
        listeAnim[ordre]=sprite;
    }

    return listeAnim;
}

