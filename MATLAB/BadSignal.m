close all;clear;clc;
%% Read file

filename = "BadAudio/bad.wav";
[y,fs] = audioread(filename);
y = y(:,1);
dt = 1/fs;
t = linspace(0, size(y,1)/fs,size(y,1));
idx = t>0.448000&t<0.449500;%t>0.444900&t<0.446070;
time = t(idx);
Amp = normalize(y(idx),'range',[-1,1]);

%% Ploting
figure;
plot(time,Amp); 
xlabel('Seconds');
ylabel('Amplitude');
title("Raw Wave(t)");
