package mobile.android.s3c6410.leds.ndk;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;

public class S3C6410LedsMain extends Activity {
    private CheckBox[] cbStrLeds = new CheckBox[4];
    private CheckBox[] cbCmdLeds = new CheckBox[4];
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        cbStrLeds[0] = (CheckBox)findViewById(R.id.checkbox_str_led1);
        cbStrLeds[1] = (CheckBox)findViewById(R.id.checkbox_str_led2);
        cbStrLeds[2] = (CheckBox)findViewById(R.id.checkbox_str_led3);
        cbStrLeds[3] = (CheckBox)findViewById(R.id.checkbox_str_led4);

        cbCmdLeds[0] = (CheckBox)findViewById(R.id.checkbox_cmd_led1);
        cbCmdLeds[1] = (CheckBox)findViewById(R.id.checkbox_cmd_led2);
        cbCmdLeds[2] = (CheckBox)findViewById(R.id.checkbox_cmd_led3);
        cbCmdLeds[3] = (CheckBox)findViewById(R.id.checkbox_cmd_led4);
    }
    
    public void onClick_ControlStr(View view)
    {
    	String str = "";
    	for(int i = 0; i < 4; i++)
    	{
        	if(cbStrLeds[i].isChecked())
        		str += "1";
        	else
        		str += "0";
    	}
    	strLeds(str);    	
    }  
    public void onClick_CmdStr(View view)
    {
    	
    	for(int i = 0; i < 4; i++)
    	{
        	if(cbCmdLeds[i].isChecked())
        		cmdLeds(1, i);
        	else
        		cmdLeds(0, i);
    	}
    	
    	
    }  

    // native方法

	public native void strLeds(String str);
	public native void cmdLeds(int cmd, int arg);

	static  
	{
		System.loadLibrary("ndk_test_s3c6410_leds");
	}
}