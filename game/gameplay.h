bool bullet_on_screen=1;
void gameplay()
{
       wizard.move();
        /////////////////////////
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        wizard.render();
        Da1.render();
        Da2.render();
        SDL_Rect hitbox= {230,wizard.getY(),1,110};
        if(!bullet_on_screen)
        {
            int n=rnd(1,1000);
            if(n>995)     A.reset(),bullet_on_screen=1;
        }
        if(bullet_on_screen)
        {
            A.move();
            A.render();
            if(checkCollision(hitbox,A.get()))
            {
                running=0;
            }
            if(A.x<0)   bullet_on_screen=0;
        }
        Da1.move();
        Da2.move();
        if(checkCollision(hitbox,Da1.get())||checkCollision(hitbox,Da2.get()))
        {
            running=0;
        }
}

