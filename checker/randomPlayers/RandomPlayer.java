import java.util.Scanner;

public class RandomPlayer {

   private static final int ME = 0;
   private static final int OPPONENT = 1;

	public static void main(String[] args){
		int turn = ME;
		
		if (args.length != 1){
			return;
      }
		if (args[0].equals("second")){
			turn = OPPONENT;
		}
		
      int message;
		Scanner s = new Scanner(System.in);

      /* first of all, get the difficulty settings from the sever */
      message = s.nextInt();

      /* then play randomly */
		for (;;){
			if (turn == ME){
				System.out.println((((int)(Math.random() * 100)) % 9) + "\n");
				System.out.flush();
			} else {
				message = s.nextInt();
            if (message == 10 || message == 11 || message == 12) {
               return;
            } else {
               /* ... */
            }
			}
			turn = (turn == ME) ? OPPONENT : ME;
		}
	}
}
