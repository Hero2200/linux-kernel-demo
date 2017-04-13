package mobile.android.s3c6410.leds.hal.java;

import mobile.android.leds.hal.service.LedHalService;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;


public class S3C6410LedHalMain extends Activity
{
	private CheckBox[] cbStrLeds = new CheckBox[4];
	LedHalService ledHalService = LedHalService.getInstance();
	@Override
	public void onCreate(Bundle savedInstanceState)
	{ 
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		cbStrLeds[0] = (CheckBox) findViewById(R.id.checkbox_str_led1);
		cbStrLeds[1] = (CheckBox) findViewById(R.id.checkbox_str_led2);
		cbStrLeds[2] = (CheckBox) findViewById(R.id.checkbox_str_led3);
		cbStrLeds[3] = (CheckBox) findViewById(R.id.checkbox_str_led4);

	}

	public void onClick_ControlStr(View view)
	{
		String str = "";
		for (int i = 0; i < 4; i++)
		{
			if (cbStrLeds[i].isChecked())
				ledHalService.setOn(i);
			else
				ledHalService.setOff(i);
		}
		
	}

	
}