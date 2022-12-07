close all;clear;clc;
%% Readin raw signal
filename = "TestPacket/TP.wav";
[y,fs] = audioread(filename);
dt = 1/fs;
time = 0:dt:(length(y)*dt)-dt;

figure;
plot(time, y);
xlabel('Seconds');
ylabel('Amplitude');
title("Raw Wave w/o Trim");

%% Trim signal to information only
start_index = 17410;   % t = 0.464293
end_index = 19444;% t = 0.518553
time_i = time(start_index : end_index);
y_i    = y(start_index : end_index);

%% Quadrature demodulation
dm = qamdemod(y_i, 2, 'bin');

%% Plot signal and demodulation result
figure;
subplot(2,1,1);
plot(time_i,y_i);
axis([time_i(1) time_i(end_index-start_index+1)  -0.01 0.01])
xlabel('Seconds');
ylabel('Amplitude');
title("Raw Wave");

subplot(2,1,2);
plot(time_i,dm); 
axis([time_i(1) time_i(end_index-start_index+1)  -0.5 1.5])
ylabel('Binary');
title("Information");