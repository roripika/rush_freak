package com.nagohiyo.rush_freak;

import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import jp.maru.mrd.IconLoader;
import jp.maru.mrd.IconCell;

public class NativeCodeAst {
    private static final int AST_ICON_WIDTH = 80;
    private static final int AST_ICON_COUNT = 4;
    private static final int DEVICE_BASE_WIDTH = 320;

    // __TEST__�̕����ɂ̓��f�B�A���ʃR�[�h�����Ă�������
    private static final String _MEDIA_CODE = "ast01235ypzxm21q4ta8";

    private static IconLoader<Integer> _iconLoader;
    private static RelativeLayout _adMain;
    
    private NativeCodeAst() {}

    public static void initAstJni()
    {
        final rush_freak activity = rush_freak.getActivity();
        // UI�X���b�h��ŁAiconLoader�̃��\�b�h�����s���邽�߂����L�q���Ă��܂�
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if (_iconLoader != null) {
                    // �ŏ��̈�񂵂��Ă�ł͂����Ȃ�
                    return;
                }
                NativeCodeAst.initAstJni_main(activity);
            }
        });
    }

    public static void showAstJni()
    {
        final rush_freak activity = rush_freak.getActivity();
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if(_iconLoader == null) {
                    Log.d("AST_DEBUG", "*** NativeCodeAst is not initialized!");
                    return ;
                }
                _iconLoader.startLoading();
                _adMain.setVisibility(View.VISIBLE);
            }
        });
    }

    public static void hideAstJni()
    {
        final rush_freak activity = rush_freak.getActivity();
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if(_iconLoader == null) {
                    Log.d("AST_DEBUG", "*** NativeCodeAst is not initialized!");
                    return ;
                }
                _iconLoader.stopLoading();
                _adMain.setVisibility(View.INVISIBLE);
            }
        });
    }

    /*
     * IconLoader ���������A�\���ʒu�ȂǏ��������郁�\�b�h
     */
    private static void initAstJni_main(rush_freak activity)
    {
        _adMain = new  RelativeLayout(activity);
        LinearLayout iconAdView = new LinearLayout(activity);

        DisplayMetrics metrics = activity.getResources().getDisplayMetrics();
        RelativeLayout.LayoutParams layoutParams;
        final int FILL_PARENT = LinearLayout.LayoutParams.FILL_PARENT;

        layoutParams = new RelativeLayout.LayoutParams(FILL_PARENT, (int)(AST_ICON_WIDTH * metrics.density));


        // ��ʂ̉����ɃA�C�R���L����z�u
        layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        iconAdView.setGravity(Gravity.CENTER_HORIZONTAL);
        iconAdView.setLayoutParams(layoutParams);

        // IconLoader�N���X�̃C���X�^���X�𐶐��B
        IconLoader<Integer> iconLoader = new IconLoader<Integer>(_MEDIA_CODE, activity);
        iconLoader.setRefreshInterval(15);

        for (int i=0; i<AST_ICON_COUNT; i++) {
            final LinearLayout iconAdSubView = new LinearLayout(activity);
            LinearLayout.LayoutParams layoutSubParams =
                    new LinearLayout.LayoutParams(1, (int)(AST_ICON_WIDTH * metrics.density), 1.0f);

            int width = metrics.widthPixels;
            int icon_width = (int)(DEVICE_BASE_WIDTH * metrics.density + 0.5f);
            if(width - icon_width > 0) {
                int iconMargin = (int)((width - icon_width) / (AST_ICON_COUNT * 2));
                layoutSubParams.setMargins(iconMargin, 0, iconMargin, 0);
            }
            iconAdSubView.setLayoutParams(layoutSubParams);

            // ��q�̃��C�A�E�gxml�t�@�C���Aicon.xml����IconCell��view�𐶐����܂��B
            View view = activity.getLayoutInflater().inflate(R.layout.icon, null);

            if (view instanceof IconCell) {
                // IconLoader ��IconCell�̃C���X�^���X��o�^���Ă����܂��B
                ((IconCell)view).addToIconLoader(iconLoader);

                // �A�C�R���̃^�C�g�������F�𔒐F�Ɏw��Bint�̐F�w��l�ŔC�ӂ̐F�ɐݒ�ł��܂��B
                ((IconCell)view).setTitleColor(0xffffffff);

                // ���C�A�E�g�p�̕ϐ�iconAdView�̂���������ɔz�u���郌�C�A�E�giconAdSubView�ɁA
                // ��������IconCell�̃C���X�^���X��z�u���Ă��܂��B
                iconAdSubView.addView(view);
            }
            iconAdView.addView(iconAdSubView);
        }
                
        _adMain.addView(iconAdView);
                
        View contentView = ((ViewGroup)activity.findViewById(android.R.id.content)).getChildAt(0);
        ((ViewGroup)contentView).addView(_adMain);
        _adMain.setVisibility(View.INVISIBLE);
                
        // IconLoader�̃C���X�^���X���Q�Ƃł���悤�ɁA���̃N���X�̃C���X�^���X��ێ����Ă����܂��B
         _iconLoader = iconLoader;
    }

}