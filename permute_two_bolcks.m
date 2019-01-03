function [xdata, ydata] = permute_two_bolcks(Xdata,Ydata)
%this function preforme one permutation between two random blocks


    p1=randi([1,length(Xdata)]);
    p2=p1;
    
    while(p1==p2)
      p2=randi([1,length(Xdata)]);  
    end
    xdata=Xdata;
    ydata= Ydata;
    
 z=xdata(p1);
 xdata(p1)=xdata(p2);
 xdata(p2)=z;
 
 z=ydata(p1);
 ydata(p1)=ydata(p2);
 ydata(p2)=z;
end



