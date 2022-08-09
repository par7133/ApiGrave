# INSTALLATION
   
  Installing ApiGrave is more straightforward than what it could appear..   
  
  First, if you use Nginx as reversed proxy just point the root of your web app to /path/to/YourApigrave/Public   
  where the public content is located:
  
  <ol>  
  <li>The static content hosted should be just of this kind: html, css, js, png, jpg, jpeg, gif, fonts, map, ico</li>   
  <li>Example of Nginx minimal configuration:
     
      server {   
     
        listen 80;
        listen [::]:80;
    
        server_name api.yourapigrave.com;
     
        root /var/www/YourApiGrave/Public;
        index index.php; 
       
        rewrite ^(/)$ /index.php?url=XMLDOC;
       
        location / {     
           
           if (!-e $request_filename) {
             rewrite ^(.+)$ /index.php?url=$1 last;
           }
        }
     
        location ~* ^.+\.(php)$ {     
          proxy_set_header Host $host;     
          proxy_set_header X-Real_IP $remote_addr;     
          proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;    
         
          proxy_http_version 1.1;     
          proxy_set_header Connection "";     
        
          proxy_pass http://127.0.0.1:8081;        
        }
        
        location ~* ^.+\.(js|map|css|jpg|jpeg|gif|png|ttf|woff|woff2|eot|pdf|html|htm|zip|flv|swf|ico|xml|txt|wav|mp3)$ {
     
          gzip on;
          #gzip_http_version 1.1;
          gzip_comp_level 6;
          gzip_types text/css text/javascript application/x-javascript text/html;
          gzip_min_length 1000;

          expires 30d;
        }      
      }     
     
     
  </li>
  </ol>  
  
  Apache instead should have DocumentRoot pointing to /path/to/YourApiGrave/Public .   
  
  Dan
