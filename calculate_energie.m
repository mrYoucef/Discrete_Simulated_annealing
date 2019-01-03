function E = calcule_energie( XData, YData, L, c)
%L lenth
%c list des of connections
    E=0;

    for i=1:length(c(:,1))
        E = E+L*(abs(XData(c(i,1))-XData(c(i,2)))+abs(YData(c(i,1))-YData(c(i,2))));
    end

end
