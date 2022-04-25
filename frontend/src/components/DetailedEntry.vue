<template>
    <div class="hcontainer">
        <h2>Historique détaillé de la partie {{entryId}}</h2>
        <div v-for='guess in guesses' :key='guess.id'>
            <word-row :solution='solution' :word='guess.word' :submitted='true'/>
        </div>
        <div v-for='i in (maxtry-(guesses.length))' :key='i'>
            <word-row :solution='solution' word='' :submitted='true'/>
        </div>
        <h3>La solution était : {{solution}}</h3>
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
.hcontainer {
    /* max-width: 1000px; */
    margin: 5px 100px;
    overflow: auto;
    border: 2px solid rgb(91, 229, 16);
    padding: 10px;
    border-radius: 5px;
}
</style>