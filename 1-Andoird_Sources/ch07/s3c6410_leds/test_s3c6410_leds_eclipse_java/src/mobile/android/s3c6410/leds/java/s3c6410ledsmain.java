package mobile.android.s3c6410.leds.java;

import java.io.FileOutputStream;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;


public class S3C6410LedsMain extends Activity
{
	private CheckBox[] cbStrLeds = new CheckBox[4];

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
				str += "1";
			else
				str += "0";
		}
		controlLeds(str);
	}

	private void controlLeds(String str)
	{
		try
		{
			FileOutputStream fos = new FileOutputStream("/dev/s3c6410_leds");
			fos.write(str.getBytes("iso-8859-1"));
			fos.close();
		}
		catch (Exception e)
		{

		}
	}
}