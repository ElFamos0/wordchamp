<template>
  <div class="">
    <div class="trucdegauche" style="width=:49%">
      <v-container>
        <v-card style="min-height:400px; box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset;">
          <h1 style="font-family: 'Roboto', sans-serif; padding: 2%">MODE CLASSIQUE</h1> <!-- msg est une variable de template -->
          <ul style="padding:2%">
            <h5 style="font-family: 'Roboto', sans-serif">
              <li> Dans le mode Classique, tu seras amené à deviner un mot. <br>
              La longueur du mot et le nombre de tentatives sont paramétrables.<br>
              <br>
              Les lettres qui s'affichent en jaune sont dans le mot à deviner mais sont mal placées.<br>
              Celles qui s'affichent en rouge sont dans le mot à deviner et sont bien placées.<br>
              <br>
              Tu gagneras 1 point par mot deviné.
              </li>
            </h5>
            <v-btn @click="this.$router.push('/redirect')" x-small color="primary" style="margin-bot : 1%">
                C'est parti !
            </v-btn>
          </ul>
        </v-card>
      </v-container>
    </div>
    <div class="trucdedroite" style="width=:49%">
      <v-container>
        <v-card style="min-height:400px; box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset;">
          <h1 style="font-family: 'Roboto', sans-serif; padding: 2%">MODE CARRIÈRE</h1> <!-- msg est une variable de template -->
          <ul style="padding:5%">
            <h5 style="font-family: 'Roboto', sans-serif">
              <li>Dans le mode carrière, c'est ta réputation qui est en jeu !<br>
              La difficulté augmente avec ton elo, la longueur du mot et le nombre de tentatives sont aléatoires.<br>
              <br>
              Si tu réussis à deviner le mot, ton elo augmente et ton classement aussi !<br>
              Si tu échoues, ils diminuent...<br>
              T'es bon, tu montes.<br>
              <br>  
              </li>
            </h5>
            
            <v-btn @click="this.$router.push('/choicecarriere')" x-small color="primary" style="margin-bot: 1%">
                C'est parti !
            </v-btn>
          </ul>
        </v-card>
      </v-container>
    </div>
  </div>
</template>

<script>
export default {
  name: 'home-page',
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
.trucdegauche {
  float:left;
  display: inline;
  width: 49%;
  padding-top: 5%;
}
/* .trucdegauche:hover {
  padding: 0%;
  transition: padding 2s
} */
.trucdedroite {
  float:right;
  display: inline;
  width: 49%;
  padding-top : 5%;
}
/* .trucdedroite:hover {
  padding: 0%;
  transition: padding 2s
} */
</style>
