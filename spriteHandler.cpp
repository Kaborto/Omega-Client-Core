#include "spriteHandler.hpp"
#include "bddInternalHandler.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;
using namespace std;

spriteHandler *spriteHandler::singleton = NULL;

//constructeur
spriteHandler::spriteHandler()
{
    cout<<"Creation du singleton spriteHandler"<<endl;
    loadSprites();
}

//destructeur vidant le map
spriteHandler::~spriteHandler()
{
    //On d�truit toutes les images restantes
    map<string, Image*>::iterator it;
    for(it = stockImages.begin(); it != stockImages.end(); it++)
    {
        delete it->second;
    }
}

//pas de moi je la comprend fichtre pas et je la supprimerais bien mais sans sa marche pas tip top
bool spriteHandler::SearchImage(const string &ImageLink, Image* &ImgTemp)
{
    map<string, Image*>::iterator it;

    it = stockImages.find(ImageLink);

    if(it == stockImages.end())
    {
        return false;
    }
    else
    {
        ImgTemp = it->second;
    }

    return true;
}

//Pr�vois la cr�ation d'une nouvelle image et son stoquage on utilise le nom du sprite comme r�ferencement et compose son url de chargement
Image *spriteHandler::CreateImage(const string &ImageLink)
{
    //on pr�pare l'image a stocker dans le map "stockImages"
    Image *ImgTemp = new Image();
    //on essait de cr�e la sf::Image en utilisant le lien fourni en param�tre en sachant que le dossier des sprites est "Sprites"
    if(ImgTemp->LoadFromFile("Sprites\\"+ImageLink+".png"))
    {
        //Si la creation � r�ussi on pense � supprimer l'affichage d'un cadre noir qui pourri tout
        ImgTemp->SetSmooth(false);
        //On peut maintenant stoquer l'image dans le map en utilisant comme identifiant le nom du sprite
        stockImages[ImageLink]=ImgTemp;
        //on renvoie l'image uniquement en cas de r�ussite
        return ImgTemp;
    }
    else
    {
        //si le chargement � �chou� on doit supprimer l'image temporaire
        delete ImgTemp;
    }

    return NULL;
}

//charge une bonne fois pour toute tout les sprites pr�vu dans la base de donn�
void spriteHandler::loadSprites()
{
    cout << "Debut de la phase de chargement des sprites\n";

    //On appel le singleton gestionnaire de la base de donn� interne
    bddInternalHandler *instBddInternalHandler = bddInternalHandler::getInstance();
    //on lui demande la liste de tous les sprites que l'on stoque dans un vecteur de string listeSprites
    vector<string> listeSprites=instBddInternalHandler->getListeSprites();

    //on parcours le vecteur pour cr�e toute les sf::Image dans la liste
    for ( vector<string>::iterator i = listeSprites.begin(); i != listeSprites.end();i++ )
    {
        //on tente de les cr�e et on en informe l'utilisateur du r�sultat
        if(CreateImage(*i))
            cout << *i << " image charger\n";
        else
            cout << *i << " image non charger\n";
    }
    cout << "Fin de la phase de chargement des sprites\n";
}


Image *spriteHandler::getImage(const string &ImageLink)
{
    Image *ImgTemp;

    //Si l'image demand�e n'existe pas d�j�, on la cr��e
    if(!SearchImage(ImageLink, ImgTemp))
    {
        ImgTemp = CreateImage(ImageLink);
    }

    return ImgTemp;
}


void spriteHandler::DeleteImage(Image &Img)
{
    map<string, Image*>::iterator it;

    //On cherche l'image demand�e
    for(it = stockImages.begin(); it != stockImages.end(); it++)
    {
    //Si on la trouve, on la d�truit et on la retire
        if(it->second == &Img)
        {
            delete &Img;
            stockImages.erase(it);
            break;
        }
    }
}


void spriteHandler::DeleteImage(const string& ImageLink)
{
    map<string, Image*>::iterator it;

    it = stockImages.find(ImageLink);

    if(it != stockImages.end())
    {
        if(it->second != NULL)
        {
            delete (it->second);
            stockImages.erase(it);
        }
    }
}
