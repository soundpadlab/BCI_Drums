function dataToSave = trainingModule(handles)
timeSlice = 5;

persistent smileData clenchData furrowData browData blinkData;

dataToSave = [];
thetaArr = [];
alphaArr = [];
bLowArr = [];
bHighArr = [];
gammaArr = [];
timeArr = [];
time = 0;

%Start broadcasting server
%!python acquisition_server_old.py &

%Listen to broadcasting server
hudpr = dsp.UDPReceiver('LocalIPPort',8888,'MessageDataType','int8');
%set (handles.status, 'String', 'recording');

tic;
while (toc<=timeSlice)
    data = strsplit(char(step(hudpr)'), ' ');
    %data
    %
    if (length(data) >= 5)
        time = toc;
        %Fetch components
%         THETA = str2double(data{1});
%         ALPHA = str2double(data{2});
%         BETA_LOW = str2double(data{3});
%         BETA_HIGH = str2double(data{4});
%         GAMMA = str2double(data{5});
%        
%         thetaArr = [thetaArr ; THETA];
%         alphaArr = [alphaArr ; ALPHA];
%         bLowArr = [bLowArr ; BETA_LOW];
%         bHighArr = [bHighArr ; BETA_HIGH];
%         gammaArr = [gammaArr ; GAMMA];
%         %[ALPHA BETA_LOW BETA_HIGH THETA GAMMA]
        timeArr = [timeArr ; time];
%        dataToSave = [dataToSave; str2double(data)];
        
        %dataToSave = [dataToSave; timeArr alphaArr bLowArr bHighArr thetaArr gammaArr];
        dataToSave = [dataToSave; str2double(data{1}) str2double(data{2}) str2double(data{3})...
                                  str2double(data{4}) str2double(data{5}) str2double(data{6})  str2double(data{7}) str2double(data{8}) str2double(data{9}) str2double(data{10}) 
                                  str2double(data{11}) str2double(data{12}) str2double(data{13})  str2double(data{14}) str2double(data{15}) str2double(data{16}) str2double(data{17}) 
                                  str2double(data{18}) str2double(data{19}) str2double(data{20})  str2double(data{21}) str2double(data{22}) str2double(data{23}) str2double(data{24}) 
                                  str2double(data{25}) str2double(data{26}) str2double(data{27})  str2double(data{28}) str2double(data{29}) str2double(data{30}) str2double(data{31}) 
                                  str2double(data{32}) str2double(data{33}) str2double(data{34})  str2double(data{35}) str2double(data{36}) str2double(data{37}) str2double(data{38}) 
                                  str2double(data{39}) str2double(data{40}) str2double(data{41})  str2double(data{42}) str2double(data{43}) str2double(data{44}) str2double(data{45}) 
                                  str2double(data{46}) str2double(data{47}) str2double(data{48})  str2double(data{49}) str2double(data{50}) str2double(data{51}) str2double(data{52}) 
                                  str2double(data{53}) str2double(data{54}) str2double(data{55})  str2double(data{56}) str2double(data{57}) str2double(data{58}) str2double(data{59}) 
                                  str2double(data{60}) str2double(data{61}) str2double(data{62})  str2double(data{63}) str2double(data{64}) str2double(data{65}) str2double(data{66}) 
                                  str2double(data{67}) str2double(data{68}) str2double(data{69})  str2double(data{70}) str2double(data{71}) str2double(data{72}) str2double(data{73}) 
                                  str2double(data{74}) str2double(data{75}) str2double(data{76})  str2double(data{77}) str2double(data{78}) str2double(data{79}) str2double(data{80}) 
                                  str2double(data{81}) str2double(data{82}) str2double(data{83})  str2double(data{84}) str2double(data{85}) str2double(data{86}) str2double(data{87}) 
                                  ];
    end
end

headers = {'Counter', 'System Time', 'Emotiv Engine Time', '1-EEG', '1-Alpha', '1-Beta_Low', '1-Beta_High', '1-Theta', '1-Gamma', '2-EEG', '2-Alpha', '2-Beta_Low', '2-Beta_High', '2-Theta', '2-Gamma', '3-EEG', '3-Alpha', '3-Beta_Low', '3-Beta_High', '3-Theta', '3-Gamma', '4-EEG', '4-Alpha', '4-Beta_Low', '4-Beta_High', '4-Theta', '4-Gamma', '5-EEG', '5-Alpha', '5-Beta_Low', '5-Beta_High', '5-Theta', '5-Gamma', '5-EEG', '6-Alpha', '6-Beta_Low', '6-Beta_High', '6-Theta', '6-Gamma', '7-EEG', '7-Alpha', '7-Beta_Low', '7-Beta_High', '7-Theta', '7-Gamma', '8-EEG', '8-Alpha', '8-Beta_Low', '8-Beta_High', '8-Theta', '8-Gamma', '9-EEG', '9-Alpha', '9-Beta_Low', '9-Beta_High', '9-Theta', '9-Gamma', '10-EEG', '10-Alpha', '10-Beta_Low', '10-Beta_High', '10-Theta', '10-Gamma', '11-EEG', '11-Alpha', '11-Beta_Low', '11-Beta_High', '11-Theta', '11-Gamma', '12-EEG', '12-Alpha', '12-Beta_Low', '12-Beta_High', '12-Theta', '12-Gamma', '13-EEG', '13-Alpha', '13-Beta_Low', '13-Beta_High', '13-Theta', '13-Gamma', '14-EEG', '14-Alpha', '14-Beta_Low', '14-Beta_High', '14-Theta', '14-Gamma'};
dataToSave = [headers; num2cell(dataToSave)];
% dataToSave
switch get(handles.action, 'UserData')
    case 'Smile'
        smileData = cat(3, smileData, dataToSave);
        dataToSave = smileData;
        
    case 'Clench'
        clenchData = cat(3, clenchData, dataToSave);
        dataToSave = clenchData;

    case 'Furrow'
        furrowData = cat(3, furrowData, dataToSave);
        dataToSave = furrowData;

    case 'Brow'
        browData = cat(3, browData, dataToSave);
        dataToSave = browData;

    case 'Blink'
        blinkData = cat(3, blinkData, dataToSave);
        dataToSave = blinkData;
end

% 
% filename = strcat(strcat(get(handles.action, 'UserData'),'-'),strcat(datestr(datetime),'.mat'));
% filename = strcat('data/', filename);
% save(filename, 'dataToSave');
% set (handles.status, 'String', 'saved');
% 
% !taskkill /im cmd.exe
