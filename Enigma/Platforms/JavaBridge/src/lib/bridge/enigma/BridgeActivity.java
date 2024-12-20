/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package lib.bridge.enigma;

import android.app.Activity;
import android.content.res.Resources;
import android.content.res.AssetManager;
import android.os.Bundle;

public class BridgeActivity extends Activity
{
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		initAssetManager(getResources().getAssets());
		initDataFilePath(getFilesDir().getAbsolutePath());
	}

	public native void initAssetManager(AssetManager mgr);
	public native void initDataFilePath(String file_dir);
}
