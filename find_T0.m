function [T0] = find_T0(XData, YData,L,C,Tho)
%find_T this function calculate initial temp according to the sytem,

% L length unit of connections
% c list des of connections
% Tho a parameter between 0 and 1 used to calculate initial temp according to the system complexity if the systeme is
% more the system is complex Tho goes higher, and that to reduce the time
% of calculation

delta=0;
XData_new =XData;
YData_new =YData;

    for i=1:100
        E=calculate_energie(XData_new,YData_new,L,C);
        [XData_new, YData_new]= permute_two_bolcks(XData_new, YData_new);
        delta=delta+abs(E-calculate_energie(XData_new,YData_new,L,C));
    end
T0 = -delta/100/log(Tho);
    
end

