function [XData,YData,Ni_e,Ni_a,E] = Simulated_annealing(C,XData,YData,L,N,tho)

% XData,YData resolved coordinates
% Ni_e total number of accepted transformations
% Ni_a total number of preformed transforamtions 


% C is n*2 matrix represents the connections
% X and Y are vecrors represents the blocks coordinates, wich will be resolved 
% L length unit of connections
% N thermodynamic equilibrium
%Tho a parameter between 0 and 1 used to calculate initial temp




Ni_e=0;% Ni_e total number of accepted transformations
Ni_a=0;% Ni_a total number of preformed transforamtions 


Na_max=12*N;%number of accepted transformations
Ne_max=100*N;%number of preformed transforamtions

Na=0;%to compute the accepted transformations 
Ne=0;%to compute preformed transformations  
N0=0;%to check the if the system didn't change 



%step1:we do 100 transformation to find the initial temp using the funion find_T 
T=find_T0(XData, YData,L,C,tho);% T initial temp

E_old=0;%to do energie comparisons
E=calculate_energie(XData, YData, L, C);

while (N0<3) %checking if the system (matrix) didn't change for 3 iterations in a row  
    
    %step 2
    [XData_new, YData_new]= permute_two_bolcks(XData, YData); %making one permutation between two elements randomly 
    E_new=calculate_energie(XData_new,YData_new,L,C);
    Ne=Ne+1;
   
    if (E_new < E||calculate_probability(E_new-E,T)>rand())
       %transformation accepted
        Na=Na+1;
        E=E_new;
        XData=XData_new;
        YData=YData_new;
    end
    
    
 
    %etape3:test if we achieved thermodynamic equilibrium
    if(Na >= Na_max  || Ne>=Ne_max)
        Ni_e=Ni_e+Ne;
        Ni_a=Ni_a+Na;
        Na=0;
        Ne=0;
        
        
       %step4:test if the system didn't changed 
        if(E_old==E)
          
          N0=N0+1;
        else
          %step5
          N0=0;
          T=0.9*T;
        end
        E_old=E;
        
      
       
            figure(3)
            G=graph(C(:,1),C(:,2));
            plot(G,'XData',XData,'YData',YData); 
    end  
end

end

