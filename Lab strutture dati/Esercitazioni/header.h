#ifdef _WIN32//di modo che system(pulisci) si portabile
#define pulisci system("cls");
#else
#ifdef linux
#define pulisci system("clear");
#endif
#endif

void pause()
{
    printf("\npremere un tasto per continuare..");
    fflush(stdin);
    getchar();
    printf("\n");
}
