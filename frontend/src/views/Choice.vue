<script>
import ChoiceSlider from '../components/ChoiceSlider.vue'
export default {
    data () {
      return {
        nbLettres: 5,
        nbTentatives: 4,
      }
    },
    name: 'choice-page',
    methods: { 
        onClick : function(nbLettres, nbTentatives) {
            this.$router.push('/word/:'+(nbLettres)+'/:'+(nbTentatives))
        }       
    },
    components: {
        ChoiceSlider
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
        <h3 style="font-family: 'Roboto', sans-serif">Sélectionne un nombre de lettres</h3>
        <choice-slider v-model=nbLettres min=5 max=9 thumbSize=24 thumbLabel="true" message="(entre 5 et 9)" style="padding-bottom: 4%"/>

    <!-- <v-subheader>Nombre de tentatives</v-subheader> -->
        <h3 style="font-family: 'Roboto', sans-serif">Sélectionne un nombre de tentatives</h3>

        <choice-slider v-model=nbTentatives min=1 max=10 thumbSize=24 thumbLabel="true" message="(max. 10)" style="padding-bottom: 4%"/>
        <v-container style="display: flex; justify-content: center">
        <div class="my-2">
            <v-btn @click="onClick(nbLettres, nbTentatives)" x-small color="primary">
                C'est parti !
            </v-btn>
        </div>
    </v-container>
  </v-card>
  
</template>

<style scoped>
</style>