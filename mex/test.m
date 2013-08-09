%% Make sure you compiled the wrapper. Check the readme file

%create some data
imdata = imread('ngc6543a.jpg');

%must convert to gray scale and single since right now the function only accepts these modalities.
img = single(rgb2gray(imdata(1:(end-100),:,:))); %removed last lines because of annotations
[l,c] = size(img);

%show the original image
figure(1); imshow(img,[]);

%create a gabor filter to process images of this size
%must usse the transpose images and dimensions because of the way matlab
%stores data
fg = opengabor(l,c,8,90,5);

%invoke the gabor filter function 
[re,im]=gaborfilt(fg,img');

%show the real, imaginary and magnitude images
figure(2); imshow(re',[]);
title('Real Part');
figure(3); imshow(im',[]);
title('Imaginary Part');
figure(4); imshow(abs(re'+sqrt(-1)*im'),[]);
title('Magnitude Part');


%destroy the gabor filter object
closegabor(fg);