function varargout = visualize(varargin)
% VISUALIZE MATLAB code for visualize.fig
%      VISUALIZE, by itself, creates a new VISUALIZE or raises the existing
%      singleton*.
%
%      H = VISUALIZE returns the handle to a new VISUALIZE or the handle to
%      the existing singleton*.
%
%      VISUALIZE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in VISUALIZE.M with the given input arguments.
%
%      VISUALIZE('Property','Value',...) creates a new VISUALIZE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before visualize_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to visualize_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help visualize

% Last Modified by GUIDE v2.5 08-Aug-2017 21:33:34

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @visualize_OpeningFcn, ...
                   'gui_OutputFcn',  @visualize_OutputFcn, ...
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


% --- Executes just before visualize is made visible.
function visualize_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to visualize (see VARARGIN)

% Choose default command line output for visualize
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes visualize wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = visualize_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in selectAction.
function selectAction_Callback(hObject, eventdata, handles)
% hObject    handle to selectAction (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns selectAction contents as cell array
%        contents{get(hObject,'Value')} returns selected item from selectAction


% --- Executes during object creation, after setting all properties.
function selectAction_CreateFcn(hObject, eventdata, handles)
% hObject    handle to selectAction (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function trialsFrom_Callback(hObject, eventdata, handles)
% hObject    handle to trialsFrom (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of trialsFrom as text
%        str2double(get(hObject,'String')) returns contents of trialsFrom as a double


% --- Executes during object creation, after setting all properties.
function trialsFrom_CreateFcn(hObject, eventdata, handles)
% hObject    handle to trialsFrom (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function trialsTo_Callback(hObject, eventdata, handles)
% hObject    handle to trialsTo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of trialsTo as text
%        str2double(get(hObject,'String')) returns contents of trialsTo as a double


% --- Executes during object creation, after setting all properties.
function trialsTo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to trialsTo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in sensorSelect.
function sensorSelect_Callback(hObject, eventdata, handles)
% hObject    handle to sensorSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns sensorSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from sensorSelect


% --- Executes during object creation, after setting all properties.
function sensorSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sensorSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in dataSelect.
function dataSelect_Callback(hObject, eventdata, handles)
% hObject    handle to dataSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns dataSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from dataSelect


% --- Executes during object creation, after setting all properties.
function dataSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to dataSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in plotButton.
function plotButton_Callback(hObject, eventdata, handles)
% hObject    handle to plotButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
gVisualize(handles);
