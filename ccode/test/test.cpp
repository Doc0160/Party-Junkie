#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char buffer[80];
int vspfunc(char *format, ...)
{
   va_list aptr;
   int ret;

   va_start(aptr, format);
   ret = vsprintf(buffer, format, aptr);
   va_end(aptr);

   return(ret);
}

int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR     CmdLine,
    int       CmdShow)
{
	srand(time(NULL));
	int score = 0;
	for(int i = 0; i < 10; i++) {
		switch(rand()%28){
			case 0:{
				if(IDNO != MessageBox(0,
					"Vous avez port� plusieurs fois le m�me short plein de sueur � la salle de sport.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 1:{
				if(IDNO != MessageBox(0,
					"Vous avez d�j� port� le m�me jean quelques semaines d�affil�e.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 2:{
				if(IDNO != MessageBox(0,
					"Retourn� votre boxer parce que vous aviez trop la flemme de faire une lessive.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 3:{
				if(IDNO != MessageBox(0,
					"Avor fait un ~test d�odeur~ sur votre boxer.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 4:{
				if(IDNO != MessageBox(0,
					"Renifl� � pleins poumons l�odeur de votre propre pet.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 5:{
				if(IDNO != MessageBox(0,
					"Repouss� l�heure de la douche pour savourer votre propre odeur.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 6:{
				if(IDNO != MessageBox(0,
					"Vous vous �tes d�j� coup� les ongles des pieds et avez laiss� les cuticules tra�ner partout.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 7:{
				if(IDNO != MessageBox(0,
					"Vous vous �tes d�j� cur� le nez et en avez examin� le contenu, la texture, les poils.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 8:{
				if(IDNO != MessageBox(0,
					"Quand il arrive que la crotte de nez refuse de sortir, vous vous mouchez vigoureusement sous la douche.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 9:{
				if(IDNO != MessageBox(0,
					"Vous vous �tes mis les mains dans le pantalon, vous avez entour� vos testicules un instant, vous avez renifl� vos doigts sans prendre la peine de vous laver les mains apr�s.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 10:{
				if(IDNO != MessageBox(0,
					"On regarde des com�dies romantiques. Seul. Pour �tre s�r que personne ne le sache.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score--;
				} else {
					score++;
				}
			} break;
			case 11:{
				if(IDNO != MessageBox(0,
					"Apr�s la grosse commission, on regarde si on a fait une belle pi�ce. Si c�est le cas, g�n�ralement on est fier de nous !",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 12:{
				if(IDNO != MessageBox(0,
					"Vous avez d�j� ex�cut� le ~palper-rouler~ quand vos couilles vous grattaient.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 13:{
				if(IDNO != MessageBox(0,
					"Vous avez d�j� utilis� le d�odorant d�un ami pour vous ~rafra�chir~.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 14:{
				if(IDNO != MessageBox(0,
					"Ou utilis� du Febreze sur des draps sales pour faire comme s�ils ~�taient tout propres~.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 15:{
				if(IDNO != MessageBox(0,
					"Vous avez d�j� mang� tout en posant votre p�che.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 16:{
				if(IDNO != MessageBox(0,
					"Vous avez pris une photo de ladite p�che et l�avez envoy�e � tous vos amis dans un tchat group�.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 17:{
				if(IDNO != MessageBox(0,
					"Vous vous �tes tenu assez loin des toilettes pour vous entra�ner � viser.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 18:{
				if(IDNO != MessageBox(0,
					"Vous avez d�j� trouv� un endroit o� vous masturber apr�s avoir �t� victime d�une gaule particuli�rement retorse.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 19:{
				if(IDNO != MessageBox(0,
					"Vous avez utilis� litt�ralement N�IMPORTE QUOI � port�e de main pour nettoyer apr�s la masturbation.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 20:{
				if(IDNO != MessageBox(0,
					"On fantasme sur nos amies. Oui ... Toutes nos amies. Sans exception.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 21:{
				if(IDNO != MessageBox(0,
					"On regarde sur internet si notre p�nis est � la bonne taille.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 22:{
				if(IDNO != MessageBox(0,
					"Dans la douche, on se mouche dans nos mains.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 23:{
				if(IDNO != MessageBox(0,
					"Seul, on se cure le nez. Parfois on fait des boules. Parfois on les jette sur une cible.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 24:{
				if(IDNO != MessageBox(0,
					"On efface nos historiques de navigation. Ou alors on passe en mode � navigation priv�e �.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score--;
				} else {
					score++;
				}
			} break;
			case 25:{
				if(IDNO != MessageBox(0,
					"On p�te sous la couette. Ensuite on la secoue.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 26:{
				if(IDNO != MessageBox(0,
					"Chaque matin quand on se l�ve, on a la gaule. Et pour pisser, on s'assoit. Et puis on utilise la technique Tour de Pise pour ne pas heurter la porcelaine des toilettes.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 27:{
				if(IDNO != MessageBox(0,
					"Laisser des gouttes d�urine sur le rebord de la cuvette.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
		}
	}
	vspfunc("Votre score de d�geulasserie: %d/10", score);
    MessageBox(0,
        buffer,
        "Party Junkie V-300",
        MB_OK | MB_ICONINFORMATION);
    return(0);
}
