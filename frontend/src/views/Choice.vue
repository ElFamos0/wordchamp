<script>
export default {
    name: 'choice-page',
    methods: { 
        onClick : function(i) {
            this.$router.push('/word/:'+(i+4))
        }       
    },
}
</script>

<template>
<div>
    <h1>
        Choisis le nombre de lettres
    </h1>
    <v-container center>
        <div class="my-2" v-for="i in 5" :key="i">
            <v-btn @click="onClick(i)" x-small color="secondary">
                {{i+4}} lettres
            </v-btn>
        </div>
    </v-container>
</div>
</template>

<style scoped>
</style>