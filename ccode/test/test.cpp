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
					"Vous avez porté plusieurs fois le même short plein de sueur à la salle de sport.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 1:{
				if(IDNO != MessageBox(0,
					"Vous avez déjà porté le même jean quelques semaines d’affilée.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 2:{
				if(IDNO != MessageBox(0,
					"Retourné votre boxer parce que vous aviez trop la flemme de faire une lessive.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 3:{
				if(IDNO != MessageBox(0,
					"Avor fait un ~test d’odeur~ sur votre boxer.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 4:{
				if(IDNO != MessageBox(0,
					"Reniflé à pleins poumons l’odeur de votre propre pet.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 5:{
				if(IDNO != MessageBox(0,
					"Repoussé l’heure de la douche pour savourer votre propre odeur.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 6:{
				if(IDNO != MessageBox(0,
					"Vous vous êtes déjà coupé les ongles des pieds et avez laissé les cuticules traîner partout.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 7:{
				if(IDNO != MessageBox(0,
					"Vous vous êtes déjà curé le nez et en avez examiné le contenu, la texture, les poils.",
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
					"Vous vous êtes mis les mains dans le pantalon, vous avez entouré vos testicules un instant, vous avez reniflé vos doigts sans prendre la peine de vous laver les mains après.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 10:{
				if(IDNO != MessageBox(0,
					"On regarde des comédies romantiques. Seul. Pour être sûr que personne ne le sache.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score--;
				} else {
					score++;
				}
			} break;
			case 11:{
				if(IDNO != MessageBox(0,
					"Après la grosse commission, on regarde si on a fait une belle pièce. Si c’est le cas, généralement on est fier de nous !",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 12:{
				if(IDNO != MessageBox(0,
					"Vous avez déjà exécuté le ~palper-rouler~ quand vos couilles vous grattaient.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 13:{
				if(IDNO != MessageBox(0,
					"Vous avez déjà utilisé le déodorant d’un ami pour vous ~rafraîchir~.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 14:{
				if(IDNO != MessageBox(0,
					"Ou utilisé du Febreze sur des draps sales pour faire comme s’ils ~étaient tout propres~.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 15:{
				if(IDNO != MessageBox(0,
					"Vous avez déjà mangé tout en posant votre pêche.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 16:{
				if(IDNO != MessageBox(0,
					"Vous avez pris une photo de ladite pêche et l’avez envoyée à tous vos amis dans un tchat groupé.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 17:{
				if(IDNO != MessageBox(0,
					"Vous vous êtes tenu assez loin des toilettes pour vous entraîner à viser.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 18:{
				if(IDNO != MessageBox(0,
					"Vous avez déjà trouvé un endroit où vous masturber après avoir été victime d’une gaule particulièrement retorse.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 19:{
				if(IDNO != MessageBox(0,
					"Vous avez utilisé littéralement N’IMPORTE QUOI à portée de main pour nettoyer après la masturbation.",
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
					"On regarde sur internet si notre pénis est à la bonne taille.",
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
					"On efface nos historiques de navigation. Ou alors on passe en mode « navigation privée ».",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score--;
				} else {
					score++;
				}
			} break;
			case 25:{
				if(IDNO != MessageBox(0,
					"On pète sous la couette. Ensuite on la secoue.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 26:{
				if(IDNO != MessageBox(0,
					"Chaque matin quand on se lève, on a la gaule. Et pour pisser, on s'assoit. Et puis on utilise la technique Tour de Pise pour ne pas heurter la porcelaine des toilettes.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
			case 27:{
				if(IDNO != MessageBox(0,
					"Laisser des gouttes d’urine sur le rebord de la cuvette.",
					"Party Junkie V-300",
					MB_YESNO | MB_ICONINFORMATION)){
						score++;
				} else {
					score--;
				}
			} break;
		}
	}
	vspfunc("Votre score de dégeulasserie: %d/10", score);
    MessageBox(0,
        buffer,
        "Party Junkie V-300",
        MB_OK | MB_ICONINFORMATION);
    return(0);
}
