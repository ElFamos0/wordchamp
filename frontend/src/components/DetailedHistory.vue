<template>
    <div class="hcontainer">
        Historique détaillé de la partie {{entryId}}
        <div v-for='word in tries1' :key='word.id'>
            <word-row :solution='solution1' :word='word.try' :submitted='true'/>
        </div>
    </div>
</template>


<script>
import WordRow from './WordRow.vue'

export default {
    name: 'DetailedHistory',
    props: {
        entryId: String,
        solution: String,
        tries: Array,
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