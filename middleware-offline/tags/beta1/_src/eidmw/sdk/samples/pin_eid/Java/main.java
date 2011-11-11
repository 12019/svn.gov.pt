//*****************************************************************************
// eID SDK sample code.
// This sample demonstrates how to use the eID SDK to change and verify the PIN
//*****************************************************************************
import java.lang.*;
import java.util.*;
import java.io.*;
import be.portugal.eid.*;

public class main
{

	//-----------------------------------------------------------------
	// verify the pin for the card in the reader
	//-----------------------------------------------------------------
	static void verifyPin()
	{
		try
		{
			PTEID_ulwrapper ulRemaining = new PTEID_ulwrapper(-1);

			PTEID_ReaderContext reader = PTEID_ReaderSet.instance().getReader();
			PTEID_EIDCard	   card   = reader.getEIDCard();

			if(card.getPins().getPinByNumber(0).verifyPin("",ulRemaining))
			{
				System.out.println("verify pin succeeded");
			}
			else
			{
				if (ulRemaining.m_long == -1)
					System.out.println("verify pin canceled");
				else
					System.out.println("verify pin failed (" + ulRemaining.m_long + " tries left)");
			}
		}
		catch(PTEID_ExCardBadType ex)
		{
			System.out.println("[Exception] This is not an eid card");
		}
		catch(PTEID_ExNoCardPresent ex)
		{
			System.out.println("[Exception] No card present");
		}
		catch(PTEID_ExNoReader ex)
		{
			System.out.println("[Exception] No reader found");
		}
		catch(PTEID_Exception ex)
		{
			System.out.println("PTEID_Exception exception");
		}
		catch(Exception ex)
		{
			System.out.println("[Exception] Other exception");
		}
	}

	//-----------------------------------------------------------------
	// change the pin for the card in the reader
	//-----------------------------------------------------------------
	static void changePin()
	{
		try
		{
			PTEID_ulwrapper ulRemaining = new PTEID_ulwrapper(-1);

			PTEID_ReaderContext reader = PTEID_ReaderSet.instance().getReader();
			PTEID_EIDCard	   card   = reader.getEIDCard();

			if(card.getPins().getPinByNumber(0).changePin("","",ulRemaining))
			{
				System.out.println("Change pin succeeded");
			}
			else
			{
				if (ulRemaining.m_long == -1)
					System.out.println("Change pin canceled");
				else
					System.out.println("Change pin failed (" + ulRemaining.m_long + " tries left)");
			}
		}
		catch(PTEID_ExCardBadType ex)
		{
			System.out.println("[Exception] This is not an eid card");
		}
		catch(PTEID_ExNoCardPresent ex)
		{
			System.out.println("[Exception] No card present");
		}
		catch(PTEID_ExNoReader ex)
		{
			System.out.println("[Exception] No reader found");
		}
		catch(PTEID_Exception ex)
		{
			System.out.println("[Exception] PTEID_Exception exception");
		}
		catch(Exception ex)
		{
			System.out.println("[Exception] Other exception");
		}
	}

	//-----------------------------------------------------------------
	// Main entry point
	//-----------------------------------------------------------------
	public static void main(String[] args)
	{
		String osName = System.getProperty("os.name");

		if (-1 != osName.indexOf("Windows"))
		{
			System.out.println("[Info]  Windows system!!");
			System.loadLibrary("pteid35libJava_Wrapper");
		}
		else
		{
			System.loadLibrary("pteidlibJava_Wrapper");
		}

		System.out.println("eID SDK sample program: pin_eid");

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		try
		{
			boolean bStop = false;

			while(!bStop)
			{
				System.out.println("   Hit v<CR> to verify the pin");
				System.out.println("       c<CR> to change the pin");
				System.out.println("       q<CR> to quit");

				String input = "";
				input = in.readLine();

				if (input.equalsIgnoreCase("v"))
				{
					verifyPin();
				}
				else if (input.equalsIgnoreCase("c"))
				{
					changePin();
				}
				else if (input.equalsIgnoreCase("q"))
				{
					bStop=true;
				}
			}

			PTEID_ReaderSet.releaseSDK();
		}
		catch (IOException ex)
		{
			System.out.println("[Exception] IOException");
		}
		catch (Exception ex)
		{
			System.out.println("[Exception] Exception");
		}
	}
}


