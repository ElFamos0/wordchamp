<template>
    <div class="detailContainer">
        <!-- <h2>Historique détaillé de la partie {{entryId}}</h2> -->
        <div v-for='guess in guesses' :key='guess.id'>
            <word-row :solution='solution' :word='guess.word' :submitted='true'/>
        </div>
        <div v-for='i in (maxtry-(guesses.length))' :key='i'>
            <word-row :solution='solution' word='' :submitted='true'/>
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
    components: {
        WordRow,
    },
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