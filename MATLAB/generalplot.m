close all;clear;clc;
%% Readin raw signal and plot them
filename = ["AudioTry/WFM.wav","AudioTry/LSB.wav","AudioTry/DSB.wav",...
             "AudioTry/USB.wav","AudioTry/CW.wav"];

figure;
p = 1;
for i = filename
    [y,fs] = audioread(i);
    dt = 1/fs;
    time = 0:dt:(length(y)*dt)-dt;
    
    subplot(2,3,p);
    p=p+1;
    plot(time,y); 
    xlabel('Seconds');
    ylabel('Amplitude');
    title("Raw Wave(t) of "+i);
end