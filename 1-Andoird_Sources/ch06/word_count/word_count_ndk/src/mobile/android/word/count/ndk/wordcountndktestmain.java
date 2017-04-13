package mobile.android.word.count.ndk;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class WordCountNDKTestMain extends Activity
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

	// native方法
	public native int readWordCountFromDev();

	public native void writeStringToDev(String str);

	static
	{
		System.loadLibrary("ndk_test_word_count");
	}
}