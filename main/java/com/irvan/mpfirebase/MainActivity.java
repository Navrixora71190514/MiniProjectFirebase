package com.irvan.mpfirebase;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Objects;

public class MainActivity extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference();

    final DatabaseReference btnStatusDB = myRef.child("node1").child("BTN");
    final DatabaseReference txtAdrValue = myRef.child("node1").child("LDR");

    private String onOff = "OFF";
    private Button iBtnOnOff;
    private TextView iTxtValue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        iBtnOnOff = findViewById(R.id.btnOnOff);
        iTxtValue = findViewById(R.id.txtAdrValue);

        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String value = Objects.requireNonNull(snapshot.child("node1/LDR").getValue()).toString();
                iTxtValue.setText(String.valueOf(value));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });

        iBtnOnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(onOff.equals("OFF")){
                    btnStatusDB.setValue("ON");
                    onOff = "ON";
                }else{
                    btnStatusDB.setValue("OFF");
                    onOff = "OFF";
                }
            }
        });
    }

}