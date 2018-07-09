package org.qtproject.example;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static MainActivity m_instance;

    public MainActivity()
    {
        m_instance = this;
    }

    public void callQt2Android()
    {
        System.out.println("TEST: Android received!");

        System.out.println("TEST: Android is calling Qt...");
        NativeFunctions.callAndroid2Qt();
    }

}
