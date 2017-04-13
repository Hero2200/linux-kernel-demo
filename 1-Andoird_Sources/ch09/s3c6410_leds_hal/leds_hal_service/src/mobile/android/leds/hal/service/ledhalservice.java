package mobile.android.leds.hal.service;
  


public class LedHalService
{
	private static LedHalService ledHalService;

	public static LedHalService getInstance()
	{
		if (ledHalService == null)
		    ledHalService = new LedHalService();
		
		return ledHalService;
	}
    
	private LedHalService()  
	{  
		init(); 
	}
    
	public boolean init()
	{
		return _init();
	} 
	public boolean setOn(int led)
	{
		return _set_on(led);
	}  
	public boolean setOff(int led)
	{ 
		return _set_off(led);
	} 
	  
	//  native method 
	private native boolean _init();

	private native boolean _set_on(int led);

	private native boolean _set_off(int led);

	static
	{
		System.load("/system/lib/led_hal_jni.so");
	}
}
