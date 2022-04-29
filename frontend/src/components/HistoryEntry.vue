<template>
    <div @click="$emit('show-details', entryId )" class="entryContainer" :style="colorClass">
      <!-- <div>(Id de la partie : {{entryId}})</div> -->
      <v-row>
        <v-col cols="3">
          <v-row class="ml-5">
            <v-col cols="12">
              <h1>{{result}}</h1>
            </v-col>
            <v-col cols="12">
              <h5>{{new Date(date).toLocaleString()}}</h5>
            </v-col>
          </v-row>
        </v-col>
        <v-col cols="2">
        </v-col>
        <v-col cols="7">
          <WordRow :animate="false" :solution="solution" :word="solution" :submitted="false" style="max-width: 100%"/>     
          <div style="padding: 10%;">
            <h5>Mode : {{type==="game_normal" ? "Classique" : "Carrière"}}</h5>
          </div>
        </v-col>
      </v-row>
    </div>
</template>


<script>
import WordRow from './WordRow.vue'
export default {
  name: 'HistoryEntry',
  props: {
    entryId : String,
    solution : String,
    result: String,
    date: String,
    type: String,
  },
  computed: {
    colorClass() {
      console.log(this.result)
      let color1 = (this.result == 'Victoire' ) ? 'green' : 'red';
      let color2 = (this.result == 'Victoire' ) ? 'rgb(118, 255, 127)' : 'rgb(255, 134, 134)';

      return 'box-shadow: rgba(0, 0, 0, 0.2) 0px 12px 28px 0px, rgba(0, 0, 0, 0.1) 0px 2px 4px 0px, rgba(255, 255, 255, 0.05) 0px 0px 0px 1px inset; background:linear-gradient('+color1+', transparent),linear-gradient(to top left, '+color2+', transparent);background-blend-mode: screen;'
    }
  },
  components: {
    WordRow
  },
  emits: ['show-details'],
}
</script>


<style scoped>

.entryContainer {
  margin: 20px 20% auto;
  overflow: hidden;
  /* border: 1px solid rgb(145, 145, 145); */
  padding: 10px;
  border-radius: 5px;
  background: rgb(205, 205, 205);
  display: flex;
}
</style>