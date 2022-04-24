<template>
    <div class="hcontainer">
        Historique détaillé de la partie {{entryId}}
        <div v-for='guess in guesses' :key='guess.id'>
            <word-row :solution='solution' :word='guess.word' :submitted='true'/>
        </div>
    </div>
</template>


<script>
import WordRow from './WordRow.vue'

export default {
    name: 'DetailedEntry',
    props: {
        entryId: String,
        solution: String,
        guesses: Array,
    },
    components: {
        WordRow,
    },
    data() {
        return {
            solution1:"test",
            tries1:[
                {id:'1', try:"sets"},
                {id:'2', try:"test"},
            ]
        }
    }
}
</script>

<style scoped>
.hcontainer {
  margin: 50px;
  overflow: auto;
  border: 2px solid rgb(91, 229, 16);
  padding: 10px;
  border-radius: 5px;
}
</style>