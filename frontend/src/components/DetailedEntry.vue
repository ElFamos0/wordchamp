<template>
    <div class="detailContainer">
        <!-- <h2>Historique détaillé de la partie {{entryId}}</h2> -->
        <div v-for='guess in guesses' :key='guess.id'>
            <word-row :animate="false" style="" :solution='solution' :word='guess.word' :submitted="true"/>
        </div>
        <div v-for='i in (maxtry-(guesses.length))' :key='i'>
            <word-row :animate="false" :solution='solution' word='' :submitted="true"/>
        </div>
        <!-- <h3>La solution était : {{solution}}</h3> -->
    </div>
</template>


<script>
import WordRow from './WordRow.vue'

export default {
    name: 'DetailedEntry',
    props: {
        entryId: String,
        solution: String,
        result: String,
        maxtry: String,
        guesses: Array,
    },
    async onMounted() {
        await new Promise(resolve => setTimeout(resolve, 500));
        //this.submits = true
    },
    components: {
        WordRow,
    },
    computed: {
        colorClass() {
      console.log(this.result)
      let color1 = (this.result == 'Victoire' ) ? 'green' : 'red';
      let color2 = (this.result == 'Victoire' ) ? 'rgb(118, 255, 127)' : 'rgb(255, 134, 134)';

      return 'box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset; background:linear-gradient('+color1+', transparent),linear-gradient(to top left, '+color2+', transparent);background-blend-mode: screen;'
    }
    }
}
</script>

<style scoped>
.detailContainer {
    /* max-width: 1000px; */
    margin-top: 5px;
    margin-right: 20%;
    margin-left: 20%;
    overflow: auto;
    /* border: 1px solid rgb(145, 145, 145); */
    padding: 10px;
    border-radius: 5px;
    background: rgb(145, 145, 145);
    /* opacity: 0.8; */

}
</style>