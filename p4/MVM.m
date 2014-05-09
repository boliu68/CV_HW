function MVM(prefix)
iniout=sprintf('%sinitial',prefix);
cmd=sprintf('CV_HW4 initial %s %s 500',prefix,iniout);
fprintf('Begin initialize');
system(cmd);
outPutVWFile(iniout,iniout);
finout=sprintf('%sfinal',prefix);
cmd=sprintf('CV_HW4 refine %s %s 5000 0.5 1 400 0.0001',iniout,finout);
fprintf('Begin refinement');
system(cmd);
outPutVWFile(finout,finout);
end