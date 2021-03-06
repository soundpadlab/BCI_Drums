function varargout = training(varargin)
% TRAINING MATLAB code for training.fig
%      TRAINING, by itself, creates a new TRAINING or raises the existing
%      singleton*.
%
%      H = TRAINING returns the handle to a new TRAINING or the handle to
%      the existing singleton*.
%
%      TRAINING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TRAINING.M with the given input arguments.
%
%      TRAINING('Property','Value',...) creates a new TRAINING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before training_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to training_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help training

% Last Modified by GUIDE v2.5 02-Jul-2017 20:40:27

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @training_OpeningFcn, ...
                   'gui_OutputFcn',  @training_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
global smileData clenchData furrowData browData blinkData relaxData;

% --- Executes just before training is made visible.
function training_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to training (see VARARGIN)

% Choose default command line output for training
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes training wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = training_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in action.
function action_Callback(hObject, eventdata, handles)
% hObject    handle to action (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns action contents as cell array
%        contents{get(hObject,'Value')} returns selected item from action


% --- Executes during object creation, after setting all properties.
function action_CreateFcn(hObject, eventdata, handles)
% hObject    handle to action (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
%if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
%    set(hObject,'BackgroundColor','black');
%end

%Start broadcasting server
!python acquisition_server_ext.py &


% --- Executes on button press in recordSwitch.
function recordSwitch_Callback(hObject, eventdata, handles)
% hObject    handle to recordSwitch (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global smileData clenchData furrowData browData blinkData relaxData;

button_state = get(hObject,'String');
if (strcmp(button_state, 'Start')==1)
	fclose(fopen('_trigger', 'w'));
    set(handles.recordSwitch, 'String', 'Stop');
    switch get(handles.action, 'Value')
        case 1
            userData = 'Smile';
            set (handles.action, 'UserData', userData);
            smileData = trainingModule_with_tempo(handles);
        case 2
            userData = 'Clench';
            set (handles.action, 'UserData', userData);
            clenchData = trainingModule_with_tempo(handles);
        case 3
            userData = 'Furrow';
            set (handles.action, 'UserData', userData);
            furrowData = trainingModule_with_tempo(handles);
        case 4
            userData = 'Brow';
            set (handles.action, 'UserData', userData);
            browData = trainingModule_with_tempo(handles);
        case 5
            userData = 'Blink';
            set (handles.action, 'UserData', userData);
            blinkData = trainingModule_with_tempo(handles);
        case 6
            userData = 'Relax';
            set (handles.action, 'UserData', userData);
            relaxData = trainingModule_with_tempo(handles);
    end
else
    delete('_trigger');
    set(handles.recordSwitch, 'String', 'Start');
    set (handles.status, 'String', '');
end


% --- Executes on button press in saveExit.
function saveExit_Callback(hObject, eventdata, handles)
% hObject    handle to saveExit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global smileData clenchData furrowData browData blinkData relaxData;

% headers = {'Time', 'Alpha', 'Beta_Low', 'Beta_High', 'Theta', 'Gamma'};
% 

timeLabel = strcat(strrep(datestr(datetime),':','-'),'.mat');
%timeLabel = '.mat';
%smile

if ~isempty(smileData)
    filename = strcat('smile-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'smileData');
    set(handles.status, 'String', 'Exported smile');
end

%clench
if ~isempty(clenchData)
    filename = strcat('clench-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'clenchData');
    set(handles.status, 'String', 'Exported clench');
end

%furrow
if ~isempty(furrowData)
    filename = strcat('furrow-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'furrowData');
    set(handles.status, 'String', 'Exported furrow');
end

%brow
if ~isempty(browData)
    filename = strcat('brow-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'browData');
    set(handles.status, 'String', 'Exported brow');
end

%blink
if ~isempty(blinkData)
    filename = strcat('blink-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'blinkData');
    set(handles.status, 'String', 'Exported blink');
end

%relax
if ~isempty(relaxData)
    filename = strcat('relax-',timeLabel);
    filename = strcat('data/', filename);
    save(filename, 'relaxData');
    set(handles.status, 'String', 'Exported relax');
end

pause on;
set(handles.status, 'String', 'Exporting data..');
pause(5);
pause off;

set (handles.status, 'String', 'exiting, good bye!');

%!killall python
!taskkill /im cmd.exe
quit;
%close(handles);
