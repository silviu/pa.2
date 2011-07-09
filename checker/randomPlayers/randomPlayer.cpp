#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>

#define ME 0
#define OPPONENT 1
#define NCOLS 9
#define UNDEF -1

int main(int argc, char * argv[])
{
   /* check that the program received precisely one argument */
   if (argc != 2) {
      return EXIT_FAILURE;
   }

   /* default to the first player, but check if you should be second */
   int turn = ME;
   if (strcmp(argv[1],"second") == 0){
      turn = OPPONENT;
   }

   int message;
   /* first of all, get the information about the difficulty setting */
   std::cin >> message;

   /* then play randomly */
   srand(time(NULL));
   for (;;){
      if (turn == ME){
         std::cout << (rand() % NCOLS) << std::endl;
         std::cout.flush();
      } else {
         std::cin >> message;
         if (message == 10 || message == 11 || message == 12){
            return EXIT_SUCCESS;
         } else {
            /* ... */
         }
      }
      turn = (turn == ME) ? OPPONENT : ME;
   }

   /* finish up */
   return EXIT_SUCCESS;
}

