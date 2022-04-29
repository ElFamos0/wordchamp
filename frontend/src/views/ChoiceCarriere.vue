<script>
import axiosAuth from '@/api/axios-auth';

export default {
    data () {
      return {
        route:  `${process.env.VUE_APP_BACKEND_URL}/choicecarriere`,
        nbLettres: 5,
        nbTentatives: 4,
        elo : 0,
      }
    },
    name: 'choicecarriere-page',
    methods: { 
        onClickRanked : function() {
            this.$router.push('/carriere/:1')
        },  
        onClickChill : function() {
            this.$router.push('/carriere/:0')
        },  
    },mounted() {
      
      // on récupère l'élo'
      axiosAuth.get(this.route)
          .then((res) => {
            // console.log(res.data)
            this.elo = res.data.elo
          });
      
    },
    unmounted() {
    
    }
}

</script>

<template>

<!-- <div style="padding-top: 2%">
    <h1 style="font-family: 'Roboto', sans-serif">
        Choisis le nombre de lettres
    </h1>
    <v-container style="display: flex; justify-content: center">
        <div class="my-2" v-for="i in 5" :key="i" style="margin: 1%">
            <v-btn @click="onClick(i)" x-small color="primary">
                {{i+4}} lettres
            </v-btn>
        </div>
    </v-container>
</div> -->
 <v-card
    flat
    color="transparent"
    width="80vw"
    style="margin-left: auto; margin-right: auto; margin-top: 7%"
  >
    <!-- <v-subheader>Nombre de lettres</v-subheader> -->
        <h1 style="font-family: 'Roboto', sans-serif">Mode carrière </h1> <br>
        <h3 style="font-family: 'Roboto', sans-serif">Sélectionne un mode de jeu</h3>
        

        <v-container style="display: flex; justify-content: center">
        <div class="my-2">
            <v-btn @click="onClickRanked()" x-small color="primary" style="margin-right: 5%" >
                Mode classé
            </v-btn>
        </div>
        <div class="my-2">
            <v-btn @click="onClickChill()" x-small color="primary" style="margin-left: 5%">
                Entraînement (non classé)
            </v-btn>
        </div>
        
        
    </v-container>
    <br>
    <h3 style="font-family: 'Roboto', sans-serif">Elo actuel : {{elo}}</h3>
    
  </v-card>
  
</template>

<style scoped>
</style>