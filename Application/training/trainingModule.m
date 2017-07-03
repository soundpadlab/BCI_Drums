function dataToSave = trainingModule(handles)
timeSlice = 5;

persistent smileData;
persistent clenchData;

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
    if (length(data) == 5)
        time = toc;
        %Fetch components
        THETA = str2double(data{1});
        ALPHA = str2double(data{2});
        BETA_LOW = str2double(data{3});
        BETA_HIGH = str2double(data{4});
        GAMMA = str2double(data{5});
       
        thetaArr = [thetaArr ; THETA];
        alphaArr = [alphaArr ; ALPHA];
        bLowArr = [bLowArr ; BETA_LOW];
        bHighArr = [bHighArr ; BETA_HIGH];
        gammaArr = [gammaArr ; GAMMA];
        %[ALPHA BETA_LOW BETA_HIGH THETA GAMMA]
        timeArr = [timeArr ; time];
        dataToSave = [dataToSave; timeArr alphaArr bLowArr bHighArr thetaArr gammaArr];
    end
end

headers = {'Time', 'Alpha', 'Beta_Low', 'Beta_High', 'Theta', 'Gamma'};
dataToSave = [headers; num2cell(dataToSave)];

switch get(handles.action, 'UserData')
    case 'Smile'
        smileData = cat(3, smileData, dataToSave);
        dataToSave = smileData;
end

% 
% filename = strcat(strcat(get(handles.action, 'UserData'),'-'),strcat(datestr(datetime),'.mat'));
% filename = strcat('data/', filename);
% save(filename, 'dataToSave');
% set (handles.status, 'String', 'saved');
% 
% !taskkill /im cmd.exe
