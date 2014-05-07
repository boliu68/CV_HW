function  outPutVWFile(slant, tilt, prefix)
z= shapeletsurf(slant, tilt,6,1,2);
[h,w]=size(slant);
fid=fopen(strcat(prefix,'.vw'),'w');
for y=1:h-1
    for x=1:w-1
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y,z(y,x),(x-1)/w,(y-1)/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(y,x+1),x/w,(y-1)/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(y+1,x),(x-1)/w,y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x,y+1,z(y+1,x),(x-1)/w,y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y+1,z(y+1,x+1),x/w,y/h);
        fprintf(fid,'%f %f %f 4 %f %f\n', x+1,y,z(y,x+1),x/w,(y-1)/h);
    end
end
fclose(fid);
end

