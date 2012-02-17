
import java.io.*;
import pteidlib.*;
import java.math.BigInteger;


public class testOficialJavaJDK{

	static
	{
		try
		{
			System.loadLibrary("pteidlibj");
		}
		catch (UnsatisfiedLinkError e)
		{
		  System.err.println("Native code library failed to load.\n" + e);
		  System.exit(1);
		}
	}

	public static void main(String[] args)
	{
		int ret = 0;
		testOficialJavaJDK test = new testOficialJavaJDK();
		
		try
		{
			// test.TestCVC();
			pteid.Init("");
			
			pteid.SetSODChecking(false);
			
			int cardtype = pteid.GetCardType();
			switch (cardtype)
			{
				case pteid.CARD_TYPE_IAS07:
					System.out.println("IAS 0.7 card\n");
					break;
				case pteid.CARD_TYPE_IAS101:
					System.out.println("IAS 1.0.1 card\n");
					break;
				case pteid.CARD_TYPE_ERR:
					System.out.println("Unable to get the card type\n");
					break;
				default:
					System.out.println("Unknown card type\n");
			  }

			
		}catch (PteidException ex)
		{
			ex.printStackTrace();
			//System.out.println(ex.getMessage());
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
			//System.out.println(ex.getMessage());
		}
	}
}