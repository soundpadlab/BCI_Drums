function [ ] = plotGraph( )
%LOTGRAPH Summary of this function goes here
%   Detailed explanation goes here
%headers = {'Counter', 'System Time', 'Emotiv Engine Time', '1-EEG', '1-Alpha', '1-Beta_Low', '1-Beta_High', '1-Theta', '1-Gamma', '2-EEG', '2-Alpha', '2-Beta_Low', '2-Beta_High', '2-Theta', '2-Gamma', '3-EEG', '3-Alpha', '3-Beta_Low', '3-Beta_High', '3-Theta', '3-Gamma', '4-EEG', '4-Alpha', '4-Beta_Low', '4-Beta_High', '4-Theta', '4-Gamma', '5-EEG', '5-Alpha', '5-Beta_Low', '5-Beta_High', '5-Theta', '5-Gamma', '5-EEG', '6-Alpha', '6-Beta_Low', '6-Beta_High', '6-Theta', '6-Gamma', '7-EEG', '7-Alpha', '7-Beta_Low', '7-Beta_High', '7-Theta', '7-Gamma', '8-EEG', '8-Alpha', '8-Beta_Low', '8-Beta_High', '8-Theta', '8-Gamma', '9-EEG', '9-Alpha', '9-Beta_Low', '9-Beta_High', '9-Theta', '9-Gamma', '10-EEG', '10-Alpha', '10-Beta_Low', '10-Beta_High', '10-Theta', '10-Gamma', '11-EEG', '11-Alpha', '11-Beta_Low', '11-Beta_High', '11-Theta', '11-Gamma', '12-EEG', '12-Alpha', '12-Beta_Low', '12-Beta_High', '12-Theta', '12-Gamma', '13-EEG', '13-Alpha', '13-Beta_Low', '13-Beta_High', '13-Theta', '13-Gamma', '14-EEG', '14-Alpha', '14-Beta_Low', '14-Beta_High', '14-Theta', '14-Gamma'};
%AF3, F7, F3, FC5, T7, P7, O1, O2, P8, T8, FC6, F4, F8, AF4

%ld = load('smile-10-Jul-2017 15-29-02.mat');
%ld = load('brow-10-Jul-2017 15-53-55.mat');
%ld = load('clench-10-Jul-2017 15-53-55.mat');
%ld = load('furrow-10-Jul-2017 15-53-55.mat');
ld = load('blink-10-Jul-2017 15-53-55.mat');

data = ld.blinkData;
t = size(data);
t = 0:1:t(1) - 1;

%RAW EEG
AF3 = squeeze(data(:,4,:));
F7 = squeeze(data(:,10,:));
F3 = squeeze(data(:,16,:));
FC5 = squeeze(data(:,22,:));
T7 = squeeze(data(:,28,:));
P7 = squeeze(data(:,34,:));
C01 = squeeze(data(:,40,:));
C02 = squeeze(data(:,46,:));
P8 = squeeze(data(:,52,:));
T8 = squeeze(data(:,58,:));
FC6 = squeeze(data(:,64,:));
F4 = squeeze(data(:,70,:));
F8 = squeeze(data(:,76,:));
AF4 = squeeze(data(:,82,:));

%ALPHA
AF3_A = squeeze(data(:,5,:));
F7_A = squeeze(data(:,11,:));
F3_A = squeeze(data(:,17,:));
FC5_A = squeeze(data(:,23,:));
T7_A = squeeze(data(:,29,:));
P7_A = squeeze(data(:,35,:));
C01_A = squeeze(data(:,41,:));
C02_A = squeeze(data(:,47,:));
P8_A = squeeze(data(:,53,:));
T8_A = squeeze(data(:,59,:));
FC6_A = squeeze(data(:,65,:));
F4_A = squeeze(data(:,71,:));
F8_A = squeeze(data(:,77,:));
AF4_A = squeeze(data(:,83,:));

%BETA_LOW
AF3_BL = squeeze(data(:,6,:));
F7_BL = squeeze(data(:,12,:));
F3_BL = squeeze(data(:,18,:));
FC5_BL = squeeze(data(:,24,:));
T7_BL = squeeze(data(:,30,:));
P7_BL = squeeze(data(:,36,:));
C01_BL = squeeze(data(:,42,:));
C02_BL = squeeze(data(:,48,:));
P8_BL = squeeze(data(:,54,:));
T8_BL = squeeze(data(:,60,:));
FC6_BL = squeeze(data(:,66,:));
F4_BL = squeeze(data(:,72,:));
F8_BL = squeeze(data(:,78,:));
AF4_BL = squeeze(data(:,84,:));

%BETA_HIGH
AF3_BH = squeeze(data(:,7,:));
F7_BH = squeeze(data(:,13,:));
F3_BH = squeeze(data(:,19,:));
FC5_BH = squeeze(data(:,25,:));
T7_BH = squeeze(data(:,31,:));
P7_BH = squeeze(data(:,37,:));
C01_BH = squeeze(data(:,43,:));
C02_BH = squeeze(data(:,49,:));
P8_BH = squeeze(data(:,55,:));
T8_BH = squeeze(data(:,61,:));
FC6_BH = squeeze(data(:,67,:));
F4_BH = squeeze(data(:,73,:));
F8_BH = squeeze(data(:,79,:));
AF4_BH = squeeze(data(:,85,:));

%THETA
AF3_T = squeeze(data(:,8,:));
F7_T = squeeze(data(:,14,:));
F3_T = squeeze(data(:,20,:));
FC5_T = squeeze(data(:,26,:));
T7_T = squeeze(data(:,32,:));
P7_T = squeeze(data(:,38,:));
C01_T = squeeze(data(:,44,:));
C02_T = squeeze(data(:,50,:));
P8_T = squeeze(data(:,56,:));
T8_T = squeeze(data(:,62,:));
FC6_T = squeeze(data(:,68,:));
F4_T = squeeze(data(:,74,:));
F8_T = squeeze(data(:,80,:));
AF4_T = squeeze(data(:,86,:));

%GAMMA
AF3_G = squeeze(data(:,4,:));
F7_G = squeeze(data(:,10,:));
F3_G = squeeze(data(:,16,:));
FC5_G = squeeze(data(:,22,:));
T7_G = squeeze(data(:,28,:));
P7_G = squeeze(data(:,34,:));
C01_G = squeeze(data(:,40,:));
C02_G = squeeze(data(:,46,:));
P8_G = squeeze(data(:,52,:));
T8_G = squeeze(data(:,58,:));
FC6_G = squeeze(data(:,64,:));
F4_G = squeeze(data(:,70,:));
F8_G = squeeze(data(:,76,:));
AF4_G = squeeze(data(:,82,:));

%PLOTS

f = figure;
p = uipanel('Parent',f,'BorderType','none'); 
p.Title = 'Blink'; 
p.TitlePosition = 'centertop'; 
p.FontSize = 12;
p.FontWeight = 'bold';


ax1 = subplot(2,3,1,'Parent', p);
plot(ax1,t,AF3);
title(ax1,'AF3-Raw EEG');
xlabel(ax1,'time');
ylabel(ax1,'amplitude');


ax2 = subplot(2,3,2,'Parent', p);
plot(ax2,t,AF3_A);
title(ax2,'AF3-Alpha');
xlabel(ax2,'time');
ylabel(ax2,'amplitude');


ax3 = subplot(2,3,3,'Parent', p);
plot(ax3,t,AF3_BL);
title(ax3,'AF3-Beta Low');
xlabel(ax3,'time');
ylabel(ax3,'amplitude');


ax4 = subplot(2,3,4,'Parent', p);
plot(ax4,t,AF3_BH);
title(ax4,'AF3-Beta High');
xlabel(ax4,'time');
ylabel(ax4,'amplitude');


ax5 = subplot(2,3,5);
plot(ax5,t,AF3_G);
title(ax5,'AF3-Gamma');
xlabel(ax5,'time');
ylabel(ax5,'amplitude');


ax6 = subplot(2,3,6);
plot(ax6,t,AF3_T);
title(ax6,'AF3-Theta');
xlabel(ax6,'time');
ylabel(ax6,'amplitude');






end



