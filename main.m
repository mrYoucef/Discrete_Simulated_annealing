%this script is only to test Simulated_annealing 


%initialization of parameters 
n=5; %matrix n*n, matrix dimentions to solve
L=5; %length unit of connections
Tho=0.8; %we consider that the system is complicated 
N=1000; %thermodynamic equilibrium

%connections list initialization for a well solved matrice

C=zeros(n*(n-1),2); %matrix 40x2 (for n=5) colum 1 (c(:,1)) represent the sources , colum 2 represent distinations (c(:,2))
k=1;
for i=1:n*n-1
    if(i>n*(n-1))
        C(k,1)=i;
        C(k,2)=i+1;
        k=k+1;
    else
        C(k,1)=i;
        C(k,2)=i+n;
        k=k+1;
         if(mod(i,n)>0)
            C(k,1)=i;
            C(k,2)=i+1;
            k=k+1;
         end
    end

end

%initialization blocs placements
XData=zeros(n*n,1);
YData=zeros(n*n,1);
for i=1:n*n
    XData(i)=mod(i-1,n);
    YData(i)= (i-1-mod(i-1,n))/n;
end

%ploting the matrix 

figure (1)
G=graph(C(:,1),C(:,2));
plot(G,'XData',XData,'YData',YData);
title("matrix before the permutations");

%perform 1000 random permutations between blocks 
for i=1:1000
 [XData, YData]= permute_two_bolcks(XData, YData);
end

 E=calculate_energie(XData, YData, L, C);
 disp("The total energie is :");
 disp(E);

figure (2)
G=graph(C(:,1),C(:,2));
plot(G,'XData',XData,'YData',YData);
title("the matrix to solve");



disp(" initiale temperature is :");
disp(find_T0(XData, YData,L,C,Tho)); 
 

[XData,YData,Ni_e,Ni_a,E] = Simulated_annealing(C,XData,YData,L,N,Tho);


figure (3)
G=graph(C(:,1),C(:,2));
plot(G,'XData',XData,'YData',YData);
title("solved matrix ");
disp("finale energie : ");
disp(calculate_energie(XData,YData,L,C));
disp("total number of preformed transforamtions:");
disp(Ni_e);
disp("total number of accepted transforamtions :");
disp(Ni_a);