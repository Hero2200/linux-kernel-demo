package mobile.android.word.count.java;

import java.io.FileInputStream;
import java.io.FileOutputStream;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class WordCountJavaTestMain extends Activity
{
	private TextView tvWordCount;
	private EditText etString;

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		tvWordCount = (TextView) findViewById(R.id.textview_wordcount);
		etString = (EditText) findViewById(R.id.edittext_string);
	}

	public void onClick_ReadWordCountFromDev(View view)
	{
		tvWordCount.setText("单词数：" + String.valueOf(readWordCountFromDev()));
	}

	public void onClick_WriteStringToDev(View view)
	{
		writeStringToDev(etString.getText().toString());

		Toast.makeText(this, "已向/dev/wordcount写入字符串", Toast.LENGTH_LONG).show();
	}

	private int readWordCountFromDev()
	{
		int n = 0;
		byte[] buffer = new byte[4];
		try
		{
			FileInputStream fis = new FileInputStream("/dev/wordcount");
			fis.read(buffer);
			n = ((int) buffer[0]) << 24 | ((int) buffer[1]) << 16
					| ((int) buffer[2]) << 8 | ((int) buffer[3]);

			fis.close();
		}
		catch (Exception e)
		{

		}
		return n;
	}

	private void writeStringToDev(String str)
	{
		try
		{
			FileOutputStream fos = new FileOutputStream("/dev/wordcount");
			fos.write(str.getBytes("iso-8859-1"));
			fos.close();
		}
		catch (Exception e)
		{

		}
	}
}