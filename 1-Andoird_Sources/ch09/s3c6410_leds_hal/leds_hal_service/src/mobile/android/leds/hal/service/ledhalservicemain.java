package mobile.android.leds.hal.service;

import android.app.Activity;
import android.os.Bundle;

public class LedHalServiceMain extends Activity
{
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		LedHalService ledHalService = LedHalService.getInstance();
		ledHalService.setOn(0);
		ledHalService.setOn(1);
		ledHalService.setOff(2);  
		ledHalService.setOn(3);
	}  
}   